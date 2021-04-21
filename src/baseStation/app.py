from flask import Flask, render_template, Response, request
from flask_socketio import SocketIO
from flask_cors import CORS
import json
from datetime import date, datetime, timedelta
from threading import Thread
import pymongo
import RPi.GPIO as GPIO  
from lib_nrf24 import NRF24
import spidev
from collections import namedtuple
from struct import unpack
import time 

# THREAD SOCKETS
import eventlet
eventlet.monkey_patch() 

# SETUP FLASK
app = Flask(__name__,
            static_folder = "./frontend/dist/static",
            template_folder = "./frontend/dist")
CORS(app)
app.config['SECRET_KEY'] = 'secret!'
app.config['DEBUG'] = True
socketio = SocketIO(app, cors_allowed_origins="*")

# SETUP RADIO
GPIO.setmode(GPIO.BCM)
pipes =  [[0xE8, 0xE8, 0xF0, 0xF0, 0xE1], [0xF0, 0xF0, 0xF0, 0xF0, 0xE1]]
radio = NRF24(GPIO, spidev.SpiDev())
radio.begin(0, 17)
radio.setPayloadSize(32)
radio.setChannel(0x76)
radio.setRetries(4, 15)
radio.setDataRate(NRF24.BR_250KBPS)
radio.setPALevel(NRF24.PA_MAX)
radio.setAutoAck(True)
radio.enableDynamicPayloads()
radio.openWritingPipe(pipes[0])
radio.openReadingPipe(1, pipes[1])
radio.printDetails()
Measurements_1 = namedtuple('Measurement1', 'index, date, time, latitude, longitude, current, voltage, wait_time')
Measurements_2 = namedtuple('Measurement2',  'index, date, time, wave_height, wave_period, water_temp, air_temp, wave_power')

# SETUP DB
myclient = pymongo.MongoClient("mongodb://localhost:27017/")
db = myclient["buoyDB"]
measurement_collection = db["buoyMeasurements"]

def radio_update():
    """
    this function runs constantly checking for new radio messages
    if it recieves one it stores the information in the mongo db
    and sends it to the dashboard
    """
    while True:
        while not radio.available(0):
            time.sleep(1/100)
        received_message = []
        radio.read(received_message, radio.getDynamicPayloadSize())
        print("received: {}".format(received_message))
        bmsg = bytes(received_message)
        values = unpack('<bIIffffh', bmsg) # little endian -> byte, unsigned long,  unsigned long, float *4, int
        if values[0] == 1:
            measurements = Measurements_1._make(values)
            dt = f'{measurements.date} {measurements.time}'
            msg = {
            'name': "location",
            'value': [measurements.latitude, measurements.longitude],
            'time': datetime.strptime(dt,'%d%m%y %H%M%S').isoformat()
            }
            send_and_save(msg)
            msg['name'] = 'current'
            msg['value'] = measurements.current
            send_and_save(msg)
            msg['name'] = 'voltage'
            msg['value'] = measurements.voltage
            send_and_save(msg)
            msg['name'] = 'wait time'
            msg['value'] = measurements.wait_time
            send_and_save(msg)
        else:
            measurements = Measurements_2._make(values)
            dt = f'{measurements.date} {measurements.time}'
            msg = {
            'name': "wave height",
            'value': measurements.wave_height,
            'time': datetime.strptime(dt,'%d%m%y %H%M%S').isoformat()
            }
            send_and_save(msg)
            msg['name'] = 'wave period'
            msg['value'] = measurements.wave_period
            send_and_save(msg)
            msg['name'] = 'wave power'
            msg['value'] = measurements.wave_power
            send_and_save(msg)
            msg['name'] = 'water temperature'
            msg['value'] = measurements.water_temp
            send_and_save(msg)
            msg['name'] = 'air temperature'
            msg['value'] = measurements.air_temp
            send_and_save(msg)


def send_and_save(measurement):
    """
    sends measurements to front end and saves them in the mongodb
    """
    if '_id' in measurement.keys():
        measurement.pop('_id')
    socketio.emit('buoy_measurement_update', json.dumps(measurement))
    measurement_collection.insert_one(measurement)

def get_results(start_date, end_date, td, measurements):
    """
    performs db query based on date and which measurements are selected
    and the granularity of the data needed
    """
    results = {}
    for measurement_name in measurements:
        pipeline = [
            { "$match": {
                "datetime": { "$gte": start_date, "$lt": end_date },
                "name": measurement_name
            }},
            { "$group": {
                "_id": {
                    "$add": [
                        { "$subtract": [
                            { "$subtract": [ "$datetime", datetime(1970,1,1) ] },
                            { "$mod": [
                                { "$subtract": [ "$datetime", datetime(1970,1,1) ] },
                               td
                            ]}
                        ] },
                        datetime(1970,1,1)
                    ],
                },
                "avg": { '$avg': "$value" }
            }},
            { "$sort": { '_id': 1}}
        ]
        for meas in measurement_collection.aggregate(pipeline):
            dt = meas["_id"].isoformat()
            if dt in results.keys():
                results[dt].append(meas["avg"])
            else:
                results[dt] = [meas["avg"]]
    # change format for chart
    results = [[key] + value for key, value in results.items()]
    return results

@app.route("/trends", methods=['POST', 'OPTIONS'])
def trendsData():
    if request.method == 'POST':
        data = request.json
        if data:
            try:
                measurements = [ name for name in data['chosenMeasurements']]
                startDate = datetime(*[int(x) for x in data['startDate'].split('-')])
                endDate = datetime(*[int(x) for x in data['endDate'].split('-')])
                granularity = int(data['granularity'])
                if (granularity == 0):
                    td = 1000*60 # 1 minute
                elif granularity == 1:
                    td = 1000*60*60 # 1 hour
                else:
                    td =  1000*60*60*24 # 1 day
                results = get_results(startDate, endDate, td, measurements)
                headers = ['Time'] + [measurment for measurment in measurements]
                data = [ headers ] + results
                return json.dumps(data), 200
            except Exception as e:
                return json.dumps({'message': 'Something is Broken'}), 500
        else:
            return json.dumps({'message': 'Something is Broken'}), 500
    else:
        return  json.dumps({'message': 'okay'}), 200

@app.route('/')
def index():
    return render_template("index.html")

if __name__ == '__main__':
    radio.startListening()
    t = Thread(target=radio_update)
    t.start()
    socketio.run(app, host='0.0.0.0')