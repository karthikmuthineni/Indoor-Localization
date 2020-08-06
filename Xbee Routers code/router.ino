#include <SoftwareSerial.h>

SoftwareSerial xbee(2,3);

bool    fHasLooped  = false;


void setup()
{
  
  Serial.begin(9600);
  
  xbee.begin(9600);
  
}

void(* resetFunc) (void) = 0; //declare reset function @ address 0

void loop()
{
  //delay(23000);
  
   if ( fHasLooped == false )
   {
       for ( int x = 0; x < 10; x++ )
       {
           xbee.write(10);
           
           delay(1000);
       }

       fHasLooped = true;
   }
   
   //delay(23000);
   
   //resetFunc();
  
  
  
}
