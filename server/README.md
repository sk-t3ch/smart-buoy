# [T3chFlicks - Smart Buoy](https://t3chflicks.com/shop/kit/smart-buoy)
## Server

This folder contains the code for the running the server for the
Smart Buoy Dashboard.

This code should be run on a Raspberry Pi, which has Python3 and mongoDB installed.

It uses Flask as a web server and communicates with the radio module (NRF24) and a mongo database.
Flask-socketio is used for communication with the frontend via websockets.

![home_screen](./ss_home.png)

![trends_screen](./ss_trends.png)

If you want to play around with the dashboard without a Smart Buoy setup then just run `python fake_data_app.py`, and you should be able to see the data coming in.

Also for development purposes there is a `populate_db.py` script which does what is says on the tin.

If you just want to see the data coming from the Buoy to the Raspberry Pi via radio then you can use the `listen_to_radio.py` script.


### Step By Step Instructions
1. Put a raspian image from [here](https://www.raspberrypi.org/downloads/) onto your pi sd card using [etcher](https://www.balena.io/etcher/).
2. Plug in the nRF24L01 before turning on as in the diagram in the electronics folder.
3. SSH into your pi (for the rest of the instructions stay in a terminal) and set up as usual [tutorial](https://www.youtube.com/watch?v=wvxCNQ5AYPg).
4. Install python3 - [tutorial](https://installvirtual.com/install-python-3-7-on-raspberry-pi/).
5. Install mongoDB - [tutorial](https://andyfelong.com/2019/01/mongodb-3-2-64-bit-running-on-raspberry-pi-3-with-caveats/).Create a DB in mongo called 'buoyDB' and a collection called 'buoyMeasurements'.
    1. `sudo apt-get install mongodb`
    2. `sudo service mongodb start`
    3. `mongo`
    4. `use buoyDB`
    5. `db.createCollection('buoyMeasurements')`
6. Install Pipenv [tutorial](https://realpython.com/pipenv-guide/)
7. Update the fields in `client/env.json` to use your google maps api key (https://developers.google.com/maps/documentation/javascript/get-api-key) and your Raspberry Pis IP address. Inside the client directory:
    1. `npm install`
    2. `npm run build`

7. Start th server:
    1. `pipenv install`
    2. `pipenv shell`
    3. `python app.py`

