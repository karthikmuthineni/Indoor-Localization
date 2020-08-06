#include <dht.h>

#include <SoftwareSerial.h>

#include <SoftwareSerial.h>
SoftwareSerial xbee(2, 3); // RX, TX
#define dataPin A0 // Defines pin number to which the sensor is connected
dht DHT; // Creats a DHT object
// XBee's DOUT (TX) is connected to pin 2 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 3 (Arduino's Software TX)
SoftwareSerial XBee(2, 3); // RX, TX
void setup()
{
   //set up both ports at 9600 baud. This value is most important
  // for the XBee. Make sure the baud rate matches the config
  // setting of your XBee.
  Serial.begin(9600);
  xbee.begin(9600);
}
void loop()
{
  int readData = DHT.read22(dataPin); // Reads the data from the sensor
  float t = DHT.temperature; // Gets the values of the temperature
  float h = DHT.humidity; // Gets the values of the humidity
 // Serial.print(t);
 // Serial.print(h);
  delay(2000);
  //xbee.write("Temp is");
  //Serial.print("Temp is");
  xbee.write(t);
  Serial.println(t);
  xbee.write("\n");
  Serial.println("\n");
  xbee.write(h);
  Serial.println(h);
 // if (Serial.available())
 // { 
    //If data comes in from serial monitor, send it out to XBee
    //int sensor = analogRead(A0);
   // XBee.println(sensor);
 //  Serial.print(A0);
  //  XBee.write(Serial.read());
 // }

 // if (XBee.available())
 // { // If data comes in from XBee, send it out to serial monitor
 //   Serial.write(XBee.read());
 // }
}
