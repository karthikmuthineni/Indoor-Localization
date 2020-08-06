#include <EEPROM.h>

#include <MatrixMath.h>

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

uint8_t data = 0;

uint8_t rssi = 0;

uint8_t dataa = 0;

#define dataPin A1

#define smoke A2

dht DHT;

#define N (2)

float D[N][N];

float E[N];

float F[N];

uint8_t payload[5] = {0, 0, 0, 0, 0};

//union u_tag {
  //  uint8_t b[4];
  //  float fval;
    //float* mval;
//} u;

XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x416c4a77);

Tx64Request tx = Tx64Request(addr64, payload, sizeof(payload));

TxStatusResponse txStatus = TxStatusResponse();

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
          //Serial.print(t);
          //Serial.print(h);
          //Serial.print(ss);
          //Serial.print(y);
          EEPROM.write(0,d1);
          

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
          //Serial.print(t);
          //Serial.print(h);
          //Serial.print(ss);
          //Serial.print(y);
          EEPROM.write(1,d2);

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
          //Serial.print(t);
          //Serial.print(h);
          //Serial.print(ss);
          //Serial.print(y);
          EEPROM.write(2,d3);
          delay(1000);
          int A = EEPROM.read(0);
          int B = EEPROM.read(1);
          int C = EEPROM.read(2);
          delay(1000);
          for (int g = 0; g < N; g++)
          {
            
            E[0] = 1 - 64 + 9 - 4 + C - A;
            E[1] = 1 - 64 + 30.2 - 4 + C - B;
            
            for (int h = 0; h < N; h++){
              D[0][0] = -14;
              D[0][1] = 2;
              D[1][0] = -14;
              D[1][1] = 7;
            }
          } 
          
          Matrix.Invert((float*)D, N);
          //Matrix.Print((float*)D, N, N, "D");
          
          Matrix.Multiply((float*)D, (float*)E, N, N, 1, (float*)F );
          //Matrix.Print((float*)D, N, N, "D");
          //Matrix.Print((float*)E, N, 1, "E");
          Matrix.Print((float*)F, N, 1, "F");
          float LP = abs((float) F[0]) ;
          float LQ = abs((float) F[1]) ;
          //Serial.print(LP);
          //Serial.println(LQ);
          
          //u.fval = t;
          //for (int r=0;r<4;r++){
            
          //payload[r]=u.b[r];
          //}
          
          payload[0] = t;
          payload[1] = h;
          payload[2] = ss;
          payload[3] = LP;
          payload[4] = LQ;
          
          xbee.send(tx);
          EEPROM.write(0,0);
          EEPROM.write(1,0);
          EEPROM.write(2,0);

        }
        else
        {
          Serial.println("No data...");
        }
          
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


