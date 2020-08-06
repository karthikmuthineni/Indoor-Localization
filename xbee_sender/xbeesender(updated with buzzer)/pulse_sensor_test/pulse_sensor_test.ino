#include <dht.h>

#include <SoftwareSerial.h>

#include <SoftwareSerial.h>

#include <dht.h>
SoftwareSerial xbee(2, 3);
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
  xbee.begin(9600);
  // Sets up to read Pulse Sensor signal every 2mS
  interruptSetup();
  
}

void loop(){
  TIM2_DIS();
  int readData=DHT.read22(dataPin);
  float t=DHT.temperature;
  float h=DHT.humidity;
  float s=analogRead(smoke);
  float ss=s/1024*5.0;
  //xbee.write(t);
  //Serial.println(t);
  //xbee.write(h);
  //Serial.println(h);
  //xbee.write(s);
  //Serial.println(s);
  //xbee.write(BPM);
  //Serial.println(BPM);
  TIM2_EN();
  // If heart beat is found
  if (QS == true) {
        
    // Print heart rate      
    //Serial.print("Heart rate: "); 
    //Serial.print("   Temperature: ");
  if (t>=45 || h>=45 || ss>=3 || BPM>=75)
  {
    xbee.write(t);
    Serial.print(t);
    //Serial.print("°C");
   // Serial.print("   Humidity: ");
    xbee.write(h);
    Serial.print(h);
    //Serial.print("%");
    //Serial.print("   Gas level:");
    xbee.write(ss);
    Serial.print(ss);
   // Serial.println("ppm");
    // Reset the Quantified Self flag for next time
    xbee.write(BPM);          
    Serial.println(BPM);
    delay(5000); 
  }
    QS = false;                       
   }
  // Wait 20 ms
  if (t>=50 || h>=43 || ss>=10 || BPM>=580)
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
}

  
  


// https://arduino.stackexchange.com/questions/21489/dht11-and-pulse-sensor-incompatibility   LINK FOR INFO ON ARDUINO, DHT11, AND PULSE SENSOR


