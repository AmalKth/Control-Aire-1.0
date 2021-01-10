#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include "Adafruit_BME680.h"
#include "RTClib.h"
RTC_DS3231 rtc;
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9341.h"
#include <SoftwareSerial.h>

#define TFT_DC 9
#define TFT_CS 10 

#define RX 2
#define TX 3

#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
#define SEALEVELPRESSURE_HPA (1013.25)

#define BLACK       0x0000      /*   0,   0,   0 */
#define NAVY        0x000F      /*   0,   0, 128 */
#define DARKGREEN   0x03E0      /*   0, 128,   0 */
#define DARKCYAN    0x03EF      /*   0, 128, 128 */
#define MAROON      0x7800      /* 128,   0,   0 */
#define PURPLE      0x780F      /* 128,   0, 128 */
#define OLIVE       0x7BE0      /* 128, 128,   0 */
#define LIGHTGREY   0xC618      /* 192, 192, 192 */
#define DARKGREY    0x7BEF      /* 128, 128, 128 */
#define BLUE        0x001F      /*   0,   0, 255 */
#define GREEN       0x07E0      /*   0, 255,   0 */
#define CYAN        0x07FF      /*   0, 255, 255 */
#define RED         0xF800      /* 255,   0,   0 */
#define MAGENTA     0xF81F      /* 255,   0, 255 */
#define YELLOW      0xFFE0      /* 255, 255,   0 */
#define WHITE       0xFFFF      /* 255, 255, 255 */
#define ORANGE      0xFD20      /* 255, 165,   0 */
#define GREENYELLOW 0xAFE5      /* 173, 255,  47 */
#define PINK        0xF81F

Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC);
Adafruit_BME680 bme; // I2C
SoftwareSerial esp8266(RX,TX);

char daysOfTheWeek[7][12] = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
int PIR = 5;              // the pin that the sensor is atteched to
//int LED = 7;

#include <SoftwareSerial.h>       //Software Serial library
SoftwareSerial espSerial(2, 3);

String apiKey = "3E52NLUWFM90QASI";    // Edit this API key according to your Account
String Host_Name = "HostName";         // Edit Host_Name
String Password = "Password";          // Edit Password
SoftwareSerial ser(2, 3);              // RX, TX

uint32_t targetTime = 0;// for next 1 second timeout
uint8_t hh,mm,ss;  //containers for current time

void setup() {                
Serial.begin(9600);                  // enable software serial
ser.begin(115200);                     // reset ESP8266
ser.println("AT+RST");               // Resetting ESP8266

//BME680 sensor setup
while (!Serial);
  Serial.println(F("BME680 test"));
  if (!bme.begin()) {
    Serial.println("Could not find a valid BME680 sensor, check wiring!");
    while (1);
  }
  
  // Set up oversampling and filter initialization
  bme.setTemperatureOversampling(BME680_OS_8X);
  bme.setHumidityOversampling(BME680_OS_2X);
  bme.setPressureOversampling(BME680_OS_4X);
  bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
  bme.setGasHeater(320, 150); // 320*C for 150 ms
  
  //RTC_clock setup
  #ifndef ESP8266
  while (!Serial); // wait for serial port to connect. Needed for native USB
#endif

  if (! rtc.begin()) {
    Serial.println("Couldn't find RTC");
    Serial.flush();
    abort();
  }

  if (rtc.lostPower()) {
    Serial.println("RTC lost power, let's set the time!");
    // When time needs to be set on a new device, or after a power loss, the
    // following line sets the RTC to the date & time this sketch was compiled
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
    // This line sets the RTC with an explicit date & time, for example to set
    // January 21, 2014 at 3am you would call:
    // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  }

  // When time needs to be re-set on a previously configured device, the
  // following line sets the RTC to the date & time this sketch was compiled
  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));
  // This line sets the RTC with an explicit date & time, for example to set
  // January 21, 2014 at 3am you would call:
  // rtc.adjust(DateTime(2014, 1, 21, 3, 0, 0));
  
  //TFT_LCD setup
  tft.begin();
  tft.setRotation(1);
  tft.fillScreen(BLACK);

  //Connecting ESP8266 to WiFi 
char inv ='"';
String cmd = "AT+CWJAP";
       cmd+= "=";
       cmd+= inv;
       cmd+= Host_Name;
       cmd+= inv;
       cmd+= ",";
       cmd+= inv;
       cmd+= Password;
       cmd+= inv;
ser.println(cmd);                    // Connecting ESP8266 to your WiFi Router
}

void loop() {
//----- BME680_sensor -----//
    if (! bme.performReading()) {
      Serial.println("Failed to perform reading :(");
      return;
      }
    Serial.print("\n");
    Serial.print("Temperature = ");
    Serial.print(bme.temperature);
    Serial.println("°C");
    Serial.print("Pressure = ");
    Serial.print(bme.pressure / 100.0);
    Serial.println(" hPa");
    Serial.print("Humidity = ");
    Serial.print(bme.humidity);
    Serial.println(" %");
    Serial.print("Gas = ");
    Serial.print(bme.gas_resistance / 1000.0);
    Serial.println(" KOhms");
    Serial.println();
    //delay(2000);

  //sending to ThingSpeak 
  float temperature = bme.temperature;       // Reading Temperature Value
  float pressure = (bme.pressure / 100.0);
  float humidity =  bme.humidity;            // Reading Humidity Value
  int getGas  = (bme.gas_resistance / 1000.0);
  String state1= String(bme.temperature);                 // Converting them to string 
  String state2= String(bme.pressure / 100.0);              // as to send it through URL
  String state3= String(bme.humidity);
  String state4= String(getGas);
  
  String cmd = "AT+CIPSTART=\"TCP\",\"";          // Establishing TCP connection
  cmd += "184.106.153.149";                       // api.thingspeak.com
  cmd += "\",80";                                 // port 80
  ser.println(cmd);
  Serial.println(cmd);
 if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }

String getStr = "GET /update?api_key=";         // prepare GET string
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(state1);                      // Temperature Data                   
  getStr +="&field2=";
  getStr += String(state2);                       // pressure Data
  getStr +="&field3=";
  getStr += String(state3);                       // Humidity Data
  getStr +="&field4=";
  getStr += String(state4);                       // Gas Data
  getStr += "\r\n\r\n";
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());                // Total Length of data
  ser.println(cmd);
  Serial.println(cmd);
  Serial.println();

if(ser.find(">")){
    ser.print(getStr);
    Serial.print(getStr);
  }
  else{
    ser.println("AT+CIPCLOSE");                  // closing connection
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
  delay(1000); // Update after every 15 seconds

 //Switching between RTC and  air quality measurements in LCD
 if (digitalRead(PIR) == LOW) { // check if the sensor is LOW
    //digitalWrite(LED, LOW);      // turn LED OFF
    sleepMode();
  } 
   else {
      //digitalWrite(LED, HIGH);      // turn LED ON
      testfillrects(BLACK,BLACK);
      DataMeasurementToLCD();
      testfillrects(BLACK,BLACK);
  }
}

void printText(char *text, uint16_t color, int x, int y,int textSize)
{
  tft.setCursor(x, y);
  tft.setTextColor(color);
  tft.setTextSize(textSize);
  tft.setTextWrap(true);
  tft.print(text);
}

void sleepMode(){  
      DateTime now = rtc.now();
      if (now.minute()<= 1) {
        tft.fillScreen(BLACK);
      }
      
      // title 
      tft.setCursor(20,30);
      tft.setTextColor(WHITE); 
      tft.setTextSize(3,3);
      tft.print("Control Aire 1.0");

      // Day
      tft.setCursor(130,80); //60,65
      tft.setTextSize(2,2);
      tft.setTextColor(CYAN);
      tft.print(daysOfTheWeek[now.dayOfTheWeek()]);
      
      //time 
      tft.fillRect(180, 110, 120, 70, BLACK);
      tft.setCursor(70,110);
      tft.setTextSize(7,7);
      tft.setTextColor(CYAN);
      tft.print(now.hour(), DEC); 
      tft.print(":");
      tft.print(now.minute(), DEC); 
      //tft.print(":");
      //tft.print(now.second(), DEC);

     //Date
     tft.setCursor(115,180); 
     tft.setTextSize(2,2);
     tft.setTextColor(CYAN);
     tft.print(now.day(), DEC); 
     tft.print(" "); 
     tft.print(now.month(), DEC); 
     tft.print(" "); 
     tft.print(now.year(), DEC); 

     //lines 
  tft.drawLine(0, 0, 320, 0, LIGHTGREY);
  tft.drawLine(0, 239, 320, 239, LIGHTGREY);
  tft.drawLine(0, 0, 0, 240, LIGHTGREY);
  tft.drawLine(319, 0, 319, 240, LIGHTGREY);
}

void DataMeasurementToLCD(){
    //title
    tft.setCursor(20, 10);
    tft.setTextColor(WHITE);
    tft.setTextSize(3,3);
    tft.setTextWrap(true);
    tft.print("Control Aire 1.0");
        
  printText("Temperature",YELLOW,10,50,2);
  printText("o",CYAN,115,75,2);
  printText("C",CYAN,130,80,3);
    tft.fillRect(20,80,90,30,BLACK);
    tft.setCursor(20,80);
    tft.setTextSize(3);
    tft.setTextWrap(true);
    tft.print(bme.temperature);
  
  printText("Humidity",YELLOW,170,50,2);
  printText("%",CYAN,290,80,3);
    tft.fillRect(180,80,90,30,BLACK);
    tft.setCursor(180,80);
    tft.setTextSize(3);
    tft.setTextWrap(true);
    tft.print(bme.humidity);

  printText("Pressure",YELLOW,10,140,2);
  printText("hPa",CYAN,50,205,2);
    tft.fillRect(20,170,130,30,BLACK);
    tft.setCursor(20,170);
    tft.setTextSize(3);
    tft.setTextWrap(true);
    tft.print(bme.readPressure() / 100.0);

  printText("Gas",YELLOW,170,140,2);
  printText("KOhms",CYAN,200,205,2);
    tft.fillRect(180,170,110,30,ILI9341_BLACK);
    tft.setCursor(180,170);
    tft.setTextSize(3);
    tft.setTextWrap(true);
    tft.print(bme.gas_resistance / 1000.0);

   //Lines 
  tft.drawLine(0, 40, 320, 40, DARKCYAN);
  tft.drawLine(160, 40, 160, 240, DARKCYAN);
  tft.drawLine(0, 130, 320, 135, DARKCYAN);
  tft.drawLine(0, 0, 320, 0, DARKCYAN);
  tft.drawLine(0, 239, 320, 239, DARKCYAN);
  tft.drawLine(0, 0, 0, 240, DARKCYAN);
  tft.drawLine(319, 0, 319, 240, DARKCYAN);
    delay(10000);
}

void testfillrects(uint16_t color1, uint16_t color2) {
  tft.fillScreen(BLACK);
  for (int16_t x=tft.width()-1; x > 6; x-=6) {
    tft.fillRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color1);
    tft.drawRect(tft.width()/2 -x/2, tft.height()/2 -x/2 , x, x, color2);
  }
}
