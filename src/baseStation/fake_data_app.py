from flask import Flask, render_template, Response, request
from flask_cors import CORS
from flask_socketio import SocketIO
import json
import time
from datetime import date, datetime, timedelta
from threading import Thread
import random

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

examples = [
  {'name': 'air temperature','range': range(25,30)},
  {'name': 'water temperature','range': range(25,30)},
  {'name': 'air pressure','range': range(25,30)},
  {'name': 'wave period', 'range': [x/10 for x in range(0, 80)]},
  {'name': 'wave height', 'range': [x/10 for x in range(0, 20)]},
  {'name': 'wave power', 'range': [x/10 for x in range(0, 20)]},
  {'name': 'location','range': [[12.015089, -61.697963]]},
  {'name': 'voltage','range': [x/10 for x in range(20, 40)]},
  {'name': 'current','range': range(-300,-100)}
  ]



def radio_update():
    """
    this function runs constantly randomly picking a
    new measurement and sending it to the dashboard
    """
    TIME_DELAY = 1 # seconds
    while 1:
      measurement = random.choice(examples)
      msg = {
        'name': measurement["name"],
        'value': random.choice(measurement["range"]),
        'time': str(datetime.now())
      }
      socketio.emit('buoy_measurement_update', json.dumps(msg))
    #   print(msg)
      time.sleep(TIME_DELAY)


@app.route("/trends", methods=['POST', 'OPTIONS'])
def trendsData():
    # {'chosenMeasurements': ['air pressure', 'wave height', 'solar'], 'startDate': '2019-07-11', 'endDate': '2019-07-12', 'granularity': 2}
    if request.method == 'POST':
        data = request.json
        if(data):
            try:
                measurements = [ name for name in data['chosenMeasurements']]
                start_date = datetime(*[int(x) for x in data['startDate'].split('-')])
                end_date = datetime(*[int(x) for x in data['endDate'].split('-')])
                granularity = int(data['granularity'])
                if (granularity == 0):
                    td = timedelta(minutes=1)
                elif granularity == 1:
                    td = timedelta(hours=1)
                else:
                    td = timedelta(days=1)
                headers = ['Time'] + [measurment for measurment in measurements]
                results = get_results(start_date, end_date, td, measurements)
                data = [ headers ] + results
                return json.dumps(data), 200
            except Exception as e:
                return json.dumps({'message': 'Something is Broken'}), 500
        else:
            return json.dumps({'message': 'Something is Broken'}), 500
    else:
        return  json.dumps({'message': 'okay'}), 200

def get_results(start_date, end_date, td, measurements):
    """
    randomly creates a set of results which between the
    start and end date within time intervals for specific
    measurments
    """
    results = []
    for dt in perdelta(start_date, end_date, td):
        results.append([dt.isoformat()] + [random.choice(next((m['range'] for m in examples if m['name'] == name), None)) for name in measurements])
    return results


def perdelta(start, end, delta):
  curr = start
  while curr <= end:
    yield curr
    curr += delta

@app.route('/')
def index():
    return render_template("index.html")

if __name__ == '__main__':
    t = Thread(target=radio_update)
    t.start()
    socketio.run(app, host='0.0.0.0')
