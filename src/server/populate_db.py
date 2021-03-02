import pymongo
import random
from datetime import date, datetime, timedelta

def get_measurements():
    examples = [
                {'name': 'air temperature','value': random.choice(range(25,30))},
                {'name': 'water temperature','value': random.choice(range(25,30))},
                {'name': 'air pressure','value': random.choice(range(25,30))},
                {'name': 'wave height', 'value': random.choice([x/10 for x in range(0, 20)])},
                {'name': 'wave period', 'value': random.choice([x/10 for x in range(0, 60)])},
                {'name': 'wave power', 'value': random.choice([x/10 for x in range(0, 20)])},
                {'name': 'location','value': random.choice([[12.015089, -61.697963]])},
                {'name': 'voltage','value': random.choice([x/10 for x in range(20, 40)])},
                {'name': 'current','value': random.choice(range(-300,-100))}
            ]
    return examples

def perdelta(start, end, delta):
  curr = start
  while curr <= end:
    yield curr
    curr += delta

myclient = pymongo.MongoClient("mongodb://localhost:27017/")
db = myclient["buoyDB"]
col = db["buoyMeasurements"]


startDate = datetime(2019, 7, 4, 0, 0, 0)
endDate = datetime(2019, 7, 12, 0, 0, 0)

for dt in perdelta(startDate, endDate, timedelta(minutes=1)):
    measurements = get_measurements()
    # could replace with insert many
    for measurement in measurements:
        measurement['datetime'] = dt
    col.insert_many(measurements)
