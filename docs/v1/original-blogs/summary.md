# Summary

We all love the seaside. As a collective, we flock to it for holidays, to enjoy water sports or to make our livelihood. But the coast is a dynamic area at the mercy of waves. Rising sea levels nibble at beaches and powerful extreme events like hurricanes completely decimate them. To understand how to save them, we need to understand the forces driving their change.

Research is expensive, but if you could create cheap, effective instruments, you would be able to generate more data – ultimately improving understanding. This was the thinking behind our Smart Buoy project. In this summary, we give you a quick run down of our project and break it down into design, the make and data presentation. Oh buoy, you’re going to love this..!

![](https://cdn-images-1.medium.com/max/2048/1*KL6fvmBq4l9Hswi-A4V2DQ.png)

### Supplies:

For the complete Smart Buoy build, you need a LOT of stuff. We will have the breakdown of specific materials required for each stage of the build in the relevant tutorial, but here’s the complete list:

* Arduino Nano — [Amazon](https://amzn.to/2jJN7xR)
* Raspberry Pi Zero — [Amazon](https://amzn.to/2jHpV3D)
* Battery \(18650\) — [Amazon](https://amzn.to/2ld11cp)
* Solar panels — [Amazon](https://amzn.to/2ld2vmZ)
* Blocking Diodes — [Amazon](https://amzn.to/2ld2X4F)
* Charge controller — [Amazon](https://amzn.to/2jJhRz0)
* Buck booster — [Amazon](https://amzn.to/2jFnCxX)
* GPS module — [Amazon](https://amzn.to/2jHgwJ2)
* GY-86 \(accelerometer, gyroscope, barometer, compass\) — [Amazon](https://amzn.to/2ld5bB3)
* Water Temperature sensor — [Amazon](https://amzn.to/2lbTASO)
* Power monitor module — [Amazon](https://amzn.to/2lbU5MG)
* Real time clock module — [Amazon](https://amzn.to/2ld6yjb)
* Radio modules — [Amazon](https://amzn.to/2l6Fq5t)
* i²c multiplexer module — [Amazon](https://amzn.to/2jJnP2S)
* 3D printer — [Amazon](https://amzn.to/2ld7xQp)
* PETG filament — [Amazon](https://amzn.to/30yw95r)
* Epoxy — [Amazon](https://amzn.to/2lbVRNQ)
* Primer spray paint — [Amazon](https://amzn.to/2ld55cE)
* Rope — [Amazon](https://amzn.to/2jHkjWM)
* Floats — [Amazon](https://amzn.to/2lfTZ6R)
* Glue — [Amazon](https://amzn.to/2jFpeaZ)

  > ## [🔗 Get The Smart Buoy Code On Github 📔](https://github.com/sk-t3ch/smart-buoy)

### What Does It Do?

The sensors on board the Smart Buoy enable it to measure: wave height, wave period, wave power, water temperature, air temperature, air pressure, voltage, current usage and GPS location.

In an ideal world, it would also have measured wave direction. Based on the measurements the Buoy did take, we were quite close to finding a solution which would enable us to calculate wave direction. However, it turned out to be pretty complicated and it’s a massive problem in the actual research community. If there’s anyone out there who can help us out and suggest an effective way to get wave direction measurements, please let us know — we’d love to understand how we could get it to work!

All the data the Buoy collects is sent via radio to a base station, which is a Raspberry Pi. We made a dashboard to display them using Vue JS.

### Build 🛠️

#### Buoy Casing

![Sand with gradually softer levels of grit](https://cdn-images-1.medium.com/max/5440/1*rW4x36liMk8T7aBrHwEtfw.png)\*

Sand with gradually softer levels of grit\*

This Buoy was probably the most difficult thing we’ve printed so far. There were just so many things to take into consideration as it was going to be in the sea, exposed to the elements and a lot of sun. We will talk more about that later in the Smart Buoy series.

In brief: we printed a near hollow sphere in two halves. The top half has slots for the solar panels and a hole for a radio aerial to go through. The bottom half has a hole for a temperature sensor to go through and a handle for a rope to be tied to.

![Spray-painting the PETG Buoy print with plastic primer filler](https://cdn-images-1.medium.com/max/5440/1*aFXDuvtOi79GmjTbhoMMFw.png)\*

Spray-painting the PETG Buoy print with plastic primer filler\*

After printing the Buoy using PETG filament, we sanded it, spray painted it with some filler primer, and then put on a couple of layers of epoxy.

![Painting epoxy on the Buoy](https://cdn-images-1.medium.com/max/5440/1*K3v708DDFfxXU0HT6v2sNw.png)\*

Painting epoxy on the Buoy\*

![Epoxy covered top half of Buoy with solar panels](https://cdn-images-1.medium.com/max/3840/1*tQb4cRb49fzHi6Qq2CRobA.png)\*

Epoxy covered top half of Buoy with solar panels\*

Once the prep of the shell was complete, we put all the electronics inside and then sealed the water temperature sensor, radio aerial and solar panels using a glue gun. Finally, we sealed the two halves with StixAll glue/adhesive \(super aeroplane glue\).

![](https://cdn-images-1.medium.com/max/5440/1*J3rMKzql-gOJYRekN-NM2A.png)

And then we hoped it was waterproof…

![](https://cdn-images-1.medium.com/max/5440/1*hRuF4mWKUt4waxQvsF71Ig.png)

#### Buoy Electronics

The Buoy has lots of sensors on board and we go into detail about these in the relevant tutorial. As this is a summary, we’ll try to keep this informative, but brief!

The Buoy is powered by an 18650 battery, which is charged by four, 5V solar panels. Only the real time clock is constantly powered, however. The Buoy uses the real time clock’s output pin to control a transistor allowing power to enter the rest of the system. When the system is turned on, it starts by getting measurements from the sensors — including a voltage value from the power monitor module. The value given by the power monitor module determines how long the system sleeps for before taking the next set of readings. An alarm is set for this time, then the system turns itself off!

![](https://cdn-images-1.medium.com/max/4686/1*yI7O6jsmqTyB3qqEJrbsPQ.png)

![](https://cdn-images-1.medium.com/max/5440/1*fQTvd5DzJbhIHQYYZLhS0Q.png)

![](https://cdn-images-1.medium.com/max/5440/1*BRzJeO_wQSEdTM4oZmlYmg.png)

The system itself is a lot of sensors and a radio module connected to an Arduino. The GY-86 module, RealTimeClock \(RTC\), Power Monitor module, and I2C multiplexer all communicate with the Arduino using I2C. We needed the I2C multiplexer is required because the GY-86 and the RTC module we used both have the same address. The multiplexer module allows you to communicate with no extra hassle, although it might be a bit overkill.

![](https://cdn-images-1.medium.com/max/12000/1*0QuwJIbJbhE7ZMeCJrILcA.jpeg)

The radio module communicates via SPI.

Originally, we had an SD card module as well, but it caused so many headaches because of the size of the SD library that we decided to scrap it.

![](https://cdn-images-1.medium.com/max/12000/1*ajFRHazByzcz1Dtc6SyWEA.jpeg)

[Take a look at the code](https://github.com/sk-t3ch/smart-buoy). It’s likely that you have some questions — probably lingering doubts as well — and we’d be happy to hear them. The in-depth tutorials include code explanations, so hopefully they will make it a bit clearer!

We tried to logically separate the code files and use a main file to include them, which seemed to work pretty well.

![](https://cdn-images-1.medium.com/max/12000/1*LpPVnU0boL0gSELHOVFJDw.jpeg)

#### Base Station Electronics

The base station is made using a Raspberry Pi Zero with a radio module attached. We got the casing from [https://www.thingiverse.com/thing:1595429](https://www.thingiverse.com/thing:1595429). You’re fab, thanks so much!

![](https://cdn-images-1.medium.com/max/2856/1*qHVsjk_rjTPO7PgNehnkfA.png)

Once you have the code running on the Arduino, it’s quite simple to get the measurements on the Raspberry Pi by running the `listen_to_radio.py` code.

#### Dashboard

To show you how we made the entire dash would be a bit of an Odyssey because it was a pretty long and complicated project. If anyone wants to know how we did it, do let us know — the T3ch Flicks resident web developer would be more than happy to do a tutorial on this!

![](https://cdn-images-1.medium.com/max/5440/1*ikBrQ-WwZzmZ-ou3GT539w.png)

Once you put these files onto a Raspberry Pi, you should be able to run the server and see the dashboard with the data coming in. For development reasons and to see what the dash would look like if it were supplied by good, regular data, we added a fake data generator into the server. Run that if you want to see what it looks like when you have more data. We’ll also explain this in some detail in a later tutorial.

> ## [🔗 Get The Smart Buoy Code On Github 📔](https://github.com/sk-t3ch/smart-buoy)

![](https://cdn-images-1.medium.com/max/5120/1*6m9rWvIMT3r4yRhqOkf_8Q.png)

![](https://cdn-images-1.medium.com/max/5120/1*CeAxVCmdnH64hF81TmDdXA.png)

### Version 2??

#### Problems

This project is absolutely not perfect — we like to think of it more as a prototype/proof of concept. Although the prototype works on a fundamental level: it floats, takes measurements and it able to transmit them, there are lots of we’ve learned and would change for version two:

1. Our biggest issue was not being able to change the code for the Buoy after gluing it shut. This was really a bit of an oversight and could be solved very effectively with a USB port covered with a rubber seal. That, however, would have added a whole other layer of complexity to the 3D print waterproofing process!
2. The algorithms we used were far from perfect. Our methods for determining wave properties were pretty crude and we ended up spending a lot of our time reading up on math for combining the sensor data from the magnetometer, accelerometer, and gyroscope. If someone out there understands this and is willing to help, we think we could make these measurements much more accurate.
3. Some of the sensors acted a little bit weirdly. The water temperature sensor was the one which stood out as being particularly dodgy — almost 10 degrees out from the real temperature at times. The reason for this could have been it just being a bad sensor, or something was heating it up…

#### Improvements

The Arduino was good, but as mentioned before we had to scrap the SD card module \(which was supposed to be the data backup if radio messages weren’t able to send\) due to memory issues. We could change it to a more powerful microcontroller like an Arduino Mega or a Teensy or just use another Raspberry Pi zero. However, this would have increased cost and power consumption.

The radio module we used has a limited range of a [couple of kilometres with direct line of sight](https://www.youtube.com/watch?v=57pdX6b0sfw).

However, in a hypothetical world where we were able to put \(very\) many Buoys around the island, we could have formed a [mesh network like this](https://www.youtube.com/watch?v=xb7psLhKTMA). There are so many possibilities for long range transmission of data, including lora, grsm. If we were able to use one of these, maybe a mesh network around the island would be possible!

### Using Our Smart Buoy for Research

We built and launched the Buoy in Grenada, a small island in the south Caribbean. While we were out there, we had a chat with the Grenadian government, who said that a Smart Buoy like the one we created would be helpful in providing quantitative measurements of ocean characteristics. Automated measurements would cut out some human effort and human error and provide helpful context for understanding changing coasts. The government also suggested that taking wind measurements would also be a helpful feature for their purposes. No idea how we’re going to manage that one, so if anyone has any ideas…

An important caveat is that although it’s a really exciting time for coastal research, particularly involving tech, there’s a long way to go before it can be fully adopted.

![](https://cdn-images-1.medium.com/max/5440/1*bX7nWPOR7mWOMnM8VZStmg.png)

### Thanks For Reading

Thanks for reading the Smart Buoy series summary blog post. If you haven’t already, please take a look at our [summary video on YouTube](https://www.youtube.com/watch?v=S-XMT6GDWk8).

[**Part 1**: Making wave and temperature measurements](https://link.medium.com/Y3knMlmmBeb)

[**Part 2**: GPS, Radio \(NRF24\) and SD Card Module](https://link.medium.com/Oev2Ia1lBeb)

[**Part 3**: Scheduling Power to the Buoy](https://link.medium.com/vte3uQdmBeb)

[**Part 4**: Waterproofing, Dashboards and Deploy!](https://link.medium.com/qEv9AIhmBeb)

I hope you have enjoyed this article. If you like the style, check out [T3chFlicks.org](https://t3chflicks.org/) for more tech focused educational content \([YouTube](https://www.youtube.com/channel/UC0eSD-tdiJMI5GQTkMmZ-6w), [Instagram](https://www.instagram.com/t3chflicks/), [Facebook](https://www.facebook.com/t3chflicks), [Twitter](https://twitter.com/t3chflicks)\).

