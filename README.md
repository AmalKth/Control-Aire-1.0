# Control-Aire-1.0 # 

#### Control Aire 1.0. detects and measures temperature, humidity, pressure and gas with a component called BME680. In idle mode, the product displays real-time clock and in active mode, it shows measurement of air quality. The measurement data will be sent via the Wi-Fi module to the ThingSpeak channel where registered data is stored in the form of graphs. The user can thus access stored data from any smartphone or computer. ####

[ThingSpeak channel for Control Aire 1.0](https://thingspeak.com/channels/1222961)
<br />
[An image of Hardware breadboard in Fritzing](https://cdn.discordapp.com/attachments/652543278243250196/797623227069366352/Breadboard_Fritzing1.png)
<br />
[Control Aire 1.0 final design image in sleep mode](https://cdn.discordapp.com/attachments/652543278243250196/797626395290894366/Control-Aire-1.0-Sleep-mode.png)
<br />
[Control Aire 1.0 final design image in measurement mode](https://cdn.discordapp.com/attachments/652543278243250196/797627403177689118/Contro-Aire-1.0-measurement_mode.png)

 #### The parts/components needed for this project to be constructed are the following: ####
 ##### 1. Arduino UNO : The brain of the procedure. #####
 ##### 2. TFT ili9340: This LCD contributes to user-friendly readings and has many functions that can be used and programmed. #####
 
 [Datasheet](https://cdn-shop.adafruit.com/datasheets/ILI9340.pdf)
 <br />
 [TFT Display adafruit Overview ](https://learn.adafruit.com/2-2-tft-display/overview)
 <br /> 
 [Guide to Interfacing TFT LCD Displays with Arduino](https://www.instructables.com/Absolute-Beginners-Guide-to-TFT-LCD-Displays-by-Ar/)
 <br /> 
 [Arduino code and wairing for LCD](https://learn.adafruit.com/2-2-tft-display?view=all)
 <br />
 [Adafruit learning system for 2.2 TFT LCD pdf](https://cdn-learn.adafruit.com/downloads/pdf/2-2-tft-display.pdf)

#####  3. BME680 : This is a sensor for temperature, humidity, pressure, altitude and gas measurements. #####

 [Datasheet](https://cdn-shop.adafruit.com/product-files/3660/BME680.pdf)
  <br /> 
 [Adafruit BME680 Overview and Wiring](https://learn.adafruit.com/adafruit-bme680-humidity-temperature-barometic-pressure-voc-gas)
 
 ##### 4. Wi-Fi module Esp8266 esp-01 : This small module allows Arduino to connect to Wi-Fi networks and make simple TCP / IP connections with Hayes-style commands / AT commands as it sends sensor data to our channel in the ThingSpeak website. #####
 
  [Datasheet](http://www.microchip.ua/wireless/esp01.pdf)
  <br />
  [How to Program ESP8266 (ESP-01) Module with Arduino UNO](https://create.arduino.cc/projecthub/pratikdesai/how-to-program-esp8266-esp-01-module-with-arduino-uno-598166)
  <br />
  [User guide for Wi-Fi microchip](https://www.itead.cc/wiki/ESP8266_Serial_WIFI_Module)
  <br />
  [An easy-to-use Arduino ESP8266 library besed on AT firmware](https://github.com/itead/ITEADLIB_Arduino_WeeESP8266)
  <br />
  [Our test channel in ThingSpeak with sensor measurements for two months](https://thingspeak.com/channels/1223435)
  <br />
##### 5. PIR sensor : (motion sensor)  This sensor detects movement in the environment up to 7 m away at a 120 degree angle. After motion is detected, measured values will be displayed on the LCD. #####

[Datasheet](https://cdn-learn.adafruit.com/downloads/pdf/pir-passive-infrared-proximity-motion-sensor.pdf)
<br />
[Adafruit overview and wairing](https://learn.adafruit.com/pir-passive-infrared-proximity-motion-sensor/overview)

##### 6. RTC (Real-time clock) : This clock is a computer clock (mostly used in integrated circuits) that keeps track of the current time displayed in the LCD during sleep mode. The real-time clock uses a separate battery that is not connected to the normal power supply. #####

[Datasheet](https://cdn-shop.adafruit.com/product-files/3013/DS3231.pdf)
<br />
[Interface DS3231 Precision RTC Module with Arduino](https://lastminuteengineers.com/ds3231-rtc-arduino-tutorial/)
<br />
[How to use RTC and wiring](https://create.arduino.cc/projecthub/MisterBotBreak/how-to-use-a-real-time-clock-module-ds3231-bc90fe)
