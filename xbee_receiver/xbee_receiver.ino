#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3); // RX, TX

void setup()
{
    Serial.begin(9600);

    Serial.println( "Arduino started receiving bytes via XBee" );

    // Set the data rate for the SoftwareSerial port.
    xbee.begin(9600);
}

void loop()  {
   if (xbee.available()) {
    byte temp= xbee.read();
    Serial.println(temp,DEC);
}


}
