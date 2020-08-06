#include <SoftwareSerial.h>

#include <SoftwareSerial.h>

SoftwareSerial xbee(2, 3); // RX, TX
char c = 'A';
int  pingPong = 1;

void setup()
{
    Serial.begin(9600);

    Serial.println( "Arduino started sending bytes via XBee" );

    //Set the data rate for the SoftwareSerial port
    xbee.begin(9600);
}

void loop() {
    // Send character via XBee to other XBee connected to Mac
    // via USB cable.
    xbee.write( c );

    //--- Display the character just sent on console. ---
    Serial.println( c );

    //--- Get the next letter in the alphabet, and reset to ---
    //--- 'A' once we have reached 'Z'.
    c = c + 1;
    if ( c>'Z' )
         c = 'A';

    //--- Switch LED on Arduino board for every character sent---
    if ( pingPong == 0 )
        digitalWrite(13, LOW);
    else
        digitalWrite(13, HIGH);
    pingPong = 1 - pingPong;
    delay( 1000 );
}
