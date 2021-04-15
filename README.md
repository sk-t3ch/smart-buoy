# [T3chFlicks](https://t3chflicks.org): Smart Buoy

[![Generic badge](https://img.shields.io/badge/Live-Demo-red.svg)](https://smart-buoy.t3chflicks.org)

> A complete ocean characteristic measuring and analytics system.
![gif_of_buoy](./smart_buoy_thumbnail_square.gif)

🎖️ Featured by [Raspberry Pi Blogs](https://www.raspberrypi.org/blog/good-buoy-the-raspberry-pi-smart-buoy/)

🎖️ Featured by [Hackaday](https://hackaday.com/2019/09/11/smart-buoy-rides-the-citizen-science-wave/)

🎖️ Featured by [Adafruit Blogs](https://blog.adafruit.com/2019/07/19/this-smart-buoy-measures-wave-height-period-power-and-more-piday-raspberrypi-raspberry_pi/)

🎖️ Featured by [Arduino](https://www.facebook.com/official.arduino/posts/3480468415312786)

🎖️ Featured by [Instructables](https://www.instructables.com/Smart-Buoy/)

🎖️ Second place [Instructables Sensor Contest](https://www.instructables.com/contest/sensors2019/)

---

## `tutorials/`
### Summary
[![Generic badge](https://img.shields.io/badge/Blog_Post-Github-orange.svg)](./summary_blog_post.md)

[![Generic badge](https://img.shields.io/badge/Blog_Post-Medium-blue.svg)](https://t3chflicks.medium.com/smart-buoy-summary-602f9db544bb)

[![Generic badge](https://img.shields.io/badge/Youtube-Video-red.svg)](https://www.youtube.com/watch?v=S-XMT6GDWk8&list=PLoTBNxUNjtjebnBR1B3RfByp8vZtZ6yL7&index=1)

 [![Everything Is AWESOME](./yt.png)](https://www.youtube.com/watch?v=aLX4btGs_x8 "Youtube Video")

### 1. Wave and Temperature Measurements
[![Generic badge](https://img.shields.io/badge/Blog_Post-Github-orange.svg)](./tutorials/1_wave_and_temperature_measurements/blog_post.md)

[![Generic badge](https://img.shields.io/badge/Blog_Post-Medium-blue.svg)](https://t3chflicks.medium.com/smart-buoy-making-wave-and-temperature-measurements-%EF%B8%8F-cdda14c52196)

[![Generic badge](https://img.shields.io/badge/Youtube-Video-red.svg)](https://www.youtube.com/watch?v=AUr0UcNb6B8&list=PLoTBNxUNjtjebnBR1B3RfByp8vZtZ6yL7&index=2)

### 2. GPS, Radio, and SD card
[![Generic badge](https://img.shields.io/badge/Blog_Post-Github-orange.svg)](./tutorials/2_gps_radio_sd/blog_post.md)

[![Generic badge](https://img.shields.io/badge/Blog_Post-Medium-blue.svg)](https://t3chflicks.medium.com/smart-buoy-gps-radio-nrf24-and-a-sd-card-module-6029af3a69d)

[![Generic badge](https://img.shields.io/badge/Youtube-Video-red.svg)](https://www.youtube.com/watch?v=xz1ix76U28E&list=PLoTBNxUNjtjebnBR1B3RfByp8vZtZ6yL7&index=3&t=160s)


### 3. Scheduling Power
[![Generic badge](https://img.shields.io/badge/Blog_Post-Github-orange.svg)](./tutorials/3_scheduling_power/blog_post.md)

[![Generic badge](https://img.shields.io/badge/Blog_Post-Medium-blue.svg)](https://t3chflicks.medium.com/smart-buoy-scheduling-power-to-the-system-81a2675fdac0)

[![Generic badge](https://img.shields.io/badge/Youtube-Video-red.svg)](https://www.youtube.com/watch?v=5guIB8_YIGQ&list=PLoTBNxUNjtjebnBR1B3RfByp8vZtZ6yL7&index=4)


### 4. Waterproofing, Dashboards and Deploy
[![Generic badge](https://img.shields.io/badge/Blog_Post-Github-orange.svg)](./tutorials/4_build_deploy/blog_post.md)

[![Generic badge](https://img.shields.io/badge/Blog_Post-Medium-blue.svg)](https://t3chflicks.medium.com/smart-buoy-waterproofing-dashboards-and-deploy-15c730bf9a3a)

[![Generic badge](https://img.shields.io/badge/Youtube-Video-red.svg)](https://www.youtube.com/watch?v=yUjocnaKXys&list=PLoTBNxUNjtjebnBR1B3RfByp8vZtZ6yL7&index=5)

---

## `src/` - contains the source code for the whole project
* `buoy/` contains the code which runs on an Arduino inside the Buoy, as well as the build files (3d model, schematic etc).

* `baseStation/` contains the code for the server, database, and dashboard.
for the dashboard which is a VueJS application

---

## 💡 Product Showcase
> ![Product](./teaser_2.png)
> ![Buoy Electronics](src/buoy/electronics/full_build_labelled.png)
> ![Buoy Electronics](src/buoy/electronics/raspberrypi_receiver_labelled.png)
> ![Buoy Dashboard Home](dashboard.png)
> ![Buoy Dashboard Trends](trends.png)
* Environment
  * Wave measurements
    * Size
    * Period
    * Power
    * Direction
    * Water temperature
  * Air
    * Temperature
    * Humidity
    * Pressure
  * Position (GPS)
* Power
  * Solar powered
  * Scheduled time for power based on battery voltage
* Radio Communication (Range 1KM)
* Interactive dashboard [![Generic badge](https://img.shields.io/badge/Live-Demo-red.svg)](https://smart-buoy.t3chflicks.org)
  * Realtime view
  * Graph historical measurements


---

This project was created by [T3chFlicks](https://t3chflicks.org) - A tech focused education and services company.

---