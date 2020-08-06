
#include <XBee.h>

#include <Average.h>

#include <dht.h>

#include <SoftwareSerial.h>

#include <SoftwareSerial.h>

#include <dht.h>

SoftwareSerial serial1(2, 3);

Average <int>sounds(10);

XBee xbee=XBee();

XBeeResponse response = XBeeResponse();

Rx16Response rx16 = Rx16Response();

Rx64Response rx64 = Rx64Response();

uint8_t option = 0;

uint8_t data = 0;

uint8_t rssi = 0;

uint8_t dataa = 0;

float D1;

float D2;

float D3;

#define dataPin A1

#define smoke A2

#define TIM2_EN() (TIMSK2=0x02)

#define TIM2_DIS() (TIMSK2=0x00)

dht DHT;
// Sensor and pins variables
int pulsePin = 0;

int blinkPin = 13;
// Pulse rate variable
volatile int BPM;    

// Raw signal
volatile int Signal;

// Interval between beats
volatile int IBI = 600;

// Becomes true when the pulse is high
volatile boolean Pulse = false;

// Becomes true when Arduino finds a pulse
volatile boolean QS = false;

void setup(){

  // Start Serial
  Serial.begin(9600);
  serial1.begin(9600);
  xbee.setSerial(serial1);
  // Sets up to read Pulse Sensor signal every 2mS
  //interruptSetup();
  
}

void loop(){
  xbee.readPacket(100);
  if (xbee.getResponse().isAvailable())
  {
    if(xbee.getResponse().getApiId() == RX_64_RESPONSE || xbee.getResponse().getApiId() == RX_16_RESPONSE)
    {
      if (xbee.getResponse().getApiId() == RX_16_RESPONSE)
      {
        xbee.getResponse().getRx16Response(rx16);
        rssi = rx16.getRssi();
        dataa = rx16.getData(0);
        sounds.push(rssi);
        float y = sounds.mean();
        if(dataa == 10)
        {
          float o = ((rssi-35));
          float d1 = pow(10, o/30);
          float D1 = pow(d1, 2);
          int readData=DHT.read22(dataPin);
          int t=DHT.temperature;
          int h=DHT.humidity;
          int s=analogRead(smoke);
          int ss=s/1024*5.0;
          Serial.print(t);
          Serial.print(h);
          Serial.print(ss);
          Serial.print(y);
          //Serial.println(D1);
        }
        else if (dataa == 8)
        {
          float m = ((rssi-35));
          float d2 = pow(10, m/30);
          float D2 = pow(d2, 2);
          int readData=DHT.read22(dataPin);
          int t=DHT.temperature;
          int h=DHT.humidity;
          int s=analogRead(smoke);
          int ss=s/1024*5.0;
          Serial.print(t);
          Serial.print(h);
          Serial.print(ss);
          Serial.print(y);
          //Serial.println(D2);
        }
        else if (dataa == 6)
        {
          float n = ((rssi-35));
          float d3 = pow(10, n/30);
          float D3 = pow(d3, 2);
          int readData=DHT.read22(dataPin);
          int t=DHT.temperature;
          int h=DHT.humidity;
          int s=analogRead(smoke);
          int ss=s/1024*5.0;
          Serial.print(t);
          Serial.print(h);
          Serial.print(ss);
          Serial.print(y);
          //Serial.println(D3);
        }
        else
        {
          Serial.println("No data...");
        }
        float F = -67+D3-D1;
        float FF = 99+D3-D2;
        int X = 0.055*FF;
        int Y = (0.071*F)+(0.031*FF);
        //Serial.println("Target Position");
        Serial.print(X);
        Serial.println(Y);
          
      }
    }
  }
}
  //xbee.write(t);
  //Serial.println(t);
  //xbee.write(h);
  //Serial.println(h);
  //xbee.write(s);
  //Serial.println(s);
  //xbee.write(BPM);
  //Serial.println(BPM);
  
  // If heart beat is found
 
  // Wait 20 ms
/*  if (t>=50 || h>=43 || ss>=10 || BPM>=580)
  {
   myTone(5,2500, 1000);
  }
  delay(2000);
    
}
void myTone(byte pin, uint16_t frequency, uint16_t duration)
{ // input parameters: Arduino pin number, frequency in Hz, duration in milliseconds
  unsigned long startTime=millis();
  unsigned long halfPeriod= 1000000L/frequency/2;
  pinMode(pin,OUTPUT);
  while (millis()-startTime< duration)
  {
    digitalWrite(pin,HIGH);
    delayMicroseconds(halfPeriod);
    digitalWrite(pin,LOW);
    delayMicroseconds(halfPeriod);
  }
  pinMode(pin,INPUT);
}*/

  
  


// https://arduino.stackexchange.com/questions/21489/dht11-and-pulse-sensor-incompatibility   LINK FOR INFO ON ARDUINO, DHT11, AND PULSE SENSOR


