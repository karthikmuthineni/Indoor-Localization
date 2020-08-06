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
    xbee.write(BPM);          
    Serial.print(BPM);
    //Serial.print("   Temperature: ");
    xbee.write(t);
    Serial.print(t);
    //Serial.print("°C");
   // Serial.print("   Humidity: ");
    xbee.write(h);
    Serial.print(h);
    //Serial.print("%");
    //Serial.print("   Gas level:");
    xbee.write(ss);
    Serial.println(ss);
   // Serial.println("ppm");
    // Reset the Quantified Self flag for next time      
    QS = false;                       
   }
  
  // Wait 20 ms
  delay(2000);
}


// https://arduino.stackexchange.com/questions/21489/dht11-and-pulse-sensor-incompatibility   LINK FOR INFO ON ARDUINO, DHT11, AND PULSE SENSOR


