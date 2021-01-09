# Control-Aire-1.0

### Control Aire 1.0. detects and measures temperature, humidity, pressure and gas with a component called BME680. In idle mode, the product displays real-time clock and in active mode, it shows measurement of air quality. ###

[ThingSpeak channel for Control Aire 1.0](https://thingspeak.com/channels/1222961/private_show)
<br /> 
 #### The parts needed for this project to be constructed are the following: ####
 ##### 1. TFT ili9340: This LCD contributes to user-friendly readings and has many functions that can be used and programmed.
 [Datasheet](https://cdn-shop.adafruit.com/datasheets/ILI9340.pdf)
 <br />
 [TFT Display adafruit Overview ](https://learn.adafruit.com/2-2-tft-display/overview)
  <br /> 
 [Arduino code and wairing for LCD](https://learn.adafruit.com/2-2-tft-display?view=all)

#####  2. BME680 : This is a sensor for temperature, humidity, pressure, altitude and gas measurements. #####
 [Datasheet](https://cdn-shop.adafruit.com/product-files/3660/BME680.pdf)
  <br /> 
 [Adafruit BME680 Overview and Wiring](https://cdn-shop.adafruit.com/product-files/3660/BME680.pdf)
 
 ##### 3. Wi-Fi module Esp8266 esp-01 : This small module allows Arduino to connect to Wi-Fi networks and make simple TCP / IP connections with Hayes-style commands / AT commands as it sends sensor data to our channel in the ThingSpeak website.
  [Datasheet](http://www.microchip.ua/wireless/esp01.pdf)
  <br />
  [User guide for Wi-Fi microchip](http://www.microchip.ua/wireless/esp01.pdf)
  <br />
  [An easy-to-use Arduino ESP8266 library besed on AT firmware](https://github.com/itead/ITEADLIB_Arduino_WeeESP8266)
  <br />
  [Our test channel in ThingSpeak with sensor measurements for two months](https://thingspeak.com/channels/1223435/private_show)
  <br />
##### 4. PIR sensor : (motion sensor) // This sensor detects movement in the environment up to 7 m away at a 120 degree angle. After motion is detected, measured values will be displayed on the LCD. #####
[Datasheet](https://cdn-learn.adafruit.com/downloads/pdf/pir-passive-infrared-proximity-motion-sensor.pdf)
 <br />
 [Adafruit overview and wairing](https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/overview)
#####



