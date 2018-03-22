#include "DHT.h"
#define DHTPIN 2     // what pin we're connected to
#define DHTTYPE DHT11   // DHT 11 
DHT dht(DHTPIN, DHTTYPE);

#include "MQ135.h"
#define MQPIN A0    //  Define Analog PIN on Arduino Board
//#define RZERO 206.85    //  Define RZERO Calibration Value
#define RZERO 206
MQ135 gasSensor = MQ135(MQPIN);

#include <SimpleTimer.h>

#include <LiquidCrystal.h>
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  Serial.begin(9600);
  float rzero = gasSensor.getRZero();
  dht.begin();
  // set LCD columns and rows:
  //lcd.begin(16, 2);
  delay(3000);
}

void readSensorData() {
  char message[60];
  // column, row
  //lcd.setCursor(0, 0);
  //lcd.print(sprintf(message,"Temperature: " , dht.readTemperature() , "%\t" , "Humidity: " , dht.readHumidity() , "*C."));
  //Serial.println(sprintf(message,"Temperature: " , dht.readTemperature() , "%\t" , "Humidity: " , dht.readHumidity() , "*C."));
  strcpy(message, "Temperature: ");
  dtostrf(dht.readTemperature(), 2, 1, &message[strlen(message)]);
  strcat(message, "*C,\tHumidity: ");
  dtostrf(dht.readHumidity(), 2, 0, &message[strlen(message)]);
  strcat(message, "%");
  Serial.println(message);

  //lcd.setCursor(0, 1);
  //lcd.print(sprintf(message,"Air quality: " , analogRead(MQPIN) , "%."));
  //Serial.println(sprintf(message,"Air quality: " , analogRead(MQPIN) , "%."));
  //lcd.print(sprintf(message,"Air quality: " , gasSensor.getPPM() , "%."));
  //Serial.println(sprintf(message, "Air quality: " , gasSensor.getPPM() , "%."));
  strcpy(message, "Air quality: ");
  dtostrf(gasSensor.getPPM(), 3, 1, &message[strlen(message)]);
  strcat(message, "ppm,\tRZero:");
  dtostrf(gasSensor.getRZero(), 4, 2, &message[strlen(message)]);
  Serial.println(message);
}

void loop() {
  readSensorData();
  delay(30 * 1000);

}
