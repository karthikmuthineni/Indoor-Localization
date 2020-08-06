#include <Average.h>

//#include <Printers.h>
#include <XBee.h>

#include <SoftwareSerial.h>

//#include <Printers.h>
#include <XBee.h>

#include <XBee.h>
#include <SoftwareSerial.h>
//#include <LiquidCrystal.h>

//LiquidCrystal lcd(12,11,5,4,3,2);

// XBee's DOUT (TX) is connected to pin 8 (Arduino's Software RX)
// XBee's DIN (RX) is connected to pin 9 (Arduino's Software TX)
SoftwareSerial serial1(2, 3); // RX, TX

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
float p;
//int Q = 'P';
uint8_t payload[] = { 'p' };
XBeeAddress64 addr64 = XBeeAddress64(0x0013a200, 0x415d8b5c);
Tx64Request tx = Tx64Request(addr64, payload, sizeof(payload));
TxStatusResponse txStatus = TxStatusResponse();
void setup() 
{
  Serial.begin(9600);
  serial1.begin(9600);
  xbee.setSerial(serial1);
  //rssi();
  //lcd.begin(16,2);
  //lcd.clear();
}

void loop() 
{
  //for (int x=0; x<=10; x++)
  //{
    //byte temp = Serial.read();
    xbee.readPacket(100);
    if (xbee.getResponse().isAvailable())
    {
      //Serial.println("available");
      if(xbee.getResponse().getApiId() == RX_64_RESPONSE || xbee.getResponse().getApiId() == RX_16_RESPONSE)
      { 
        //Serial.println("16");
        if (xbee.getResponse().getApiId() == RX_16_RESPONSE) 
        {
          //Serial.println("16");
          xbee.getResponse().getRx16Response(rx16);
          //option = rx16.getOption();
          //data = rx16.getData(0);
          //Serial.print(temp);
          //if (temp == 255)
          //{
            rssi = rx16.getRssi();
            dataa = rx16.getData(0);
          //Serial.print("data: ");Serial.println(data);
          //Serial.print("option: ");Serial.println(option);
      //    lcd.clear();
      //    lcd.print(rssi);
            //Serial.print(temp);
            sounds.push(rssi);
            //Serial.print("xbee1 :");
            float y = sounds.mean();
            Serial.println(y);
            //Serial.println(dataa);
          //}
            if (dataa == 10)
           { 
              float p = ((rssi-35));
            //Serial.println(p);
              float d1 = pow(10, p/30);
            //Serial.print("distance: ");
              Serial.println(d1);
              float D1 = pow (d1, 2);
              xbee.send(tx);
              
           }
           else if (dataa == 8)
           {
             float q = ((rssi-35));
             float d2 = pow(10, q/30);
             Serial.println(d2);
             float D2 = pow(d2, 2);
             
           }
           else if (dataa == 6)
           {
             float r = ((rssi-35));
             float d3 = pow(10, r/30);
             Serial.println(d3);
             float D3 = pow(d3, 2);
           }
           else
           {
             Serial.println("no data");
           }
           float F = -67+D3-D1;
           float FF = 99+D3-D2;
           int X = 0.055*FF;
           int Y = (0.071*F)+(0.031*FF);
           Serial.println("Target Position");
           Serial.print(X);
           Serial.println(Y);
           
        }
        
        else 
        {
          Serial.println("64");
          xbee.getResponse().getRx64Response(rx64);
          //option = rx64.getOption();
          //data = rx64.getData(0);
          rssi = rx64.getRssi();
        //  lcd.clear();
        //  lcd.print(rssi);
          Serial.println(rssi);
        }
        
      }
    }
  }
//}

