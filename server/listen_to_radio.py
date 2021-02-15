import RPi.GPIO as GPIO
from lib_nrf24 import NRF24
import time
import spidev
from struct import unpack
from collections import namedtuple
import datetime

Measurement_1 = namedtuple('Measurement1', 'index date time latitude, longitude, current, voltage, wait_time')
Measurement_2 = namedtuple('Measurement2',  'index date time wave_height, wave_period, water_temp, air_temp, wave_power')


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
radio.startListening()

while True:
    while not radio.available(0):
        time.sleep(1/100)

    received_message = []
    radio.read(received_message, radio.getDynamicPayloadSize())
    print("received: {}".format(received_message))
    bmsg = bytes(received_message)
    values = unpack('<bIIffffh', bmsg)

    if values[0] == 1:
        measurement = Measurement_1._make(values)
    else:
        measurement = Measurement_2._make(values)

    print(datetime.datetime.now())
    print(measurement)
    print()
