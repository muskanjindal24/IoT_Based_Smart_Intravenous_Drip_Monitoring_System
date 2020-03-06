#include "HX711.h"
#include <SoftwareSerial.h>

#define calibration_factor -7050.0 //This value is obtained using the SparkFun_HX711_Calibration sketch

#define DOUT  A0
#define CLK  A1

HX711 scale;

SoftwareSerial mySerial(9,10); // receiver and transmitter pins
const int positive = 13, ground = 12; // the pins are made as input supply
int const invert = 11; //load sensor’s inverting signal
int const non_invert = 10; //load sensor’s non -inverting signal

void setup() {
  Serial.begin(9600);
  Serial.println("HX711 scale demo");

  scale.begin(DOUT, CLK);
  scale.set_scale(calibration_factor); //This value is obtained by using the SparkFun_HX711_Calibration sketch
  scale.tare(); //Assuming there is no weight on the scale at start up, reset the scale to 0
  Serial.println("Readings:");

  digitalWrite(positive, HIGH);
  digitalWrite(ground, LOW); //input supply
  
  mySerial.begin(9600); // Setting the baud rate of GSM Module
  delay(100); 
}

void loop() {
  Serial.print("Reading: ");
  int result = analogRead(scale.get_units());
  //Serial.print(scale.get_units()); //scale.get_units() returns a float
  //Serial.print(" kg"); //You can change this to kg but you'll need to refactor the calibration_factor
  Serial.print(result);
  Serial.println();
     if(result==386)
       {
          Serial.println("Alert");
          mySerial.println("AT+CMGF=1");
          delay(1000);
          mySerial.println("AT+CMGS=\"+919016231815\"\r"); //Enter mobile number
          delay(1000);
          mySerial.println("SMS from GSM Module");//SMS text you want to send
          delay(1000);
          mySerial.println((char)26); // aASCII code of CTRL+Z
          delay(1000);
        }
  }
