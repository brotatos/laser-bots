/* Simple test of the functionality of the photo resistor

Connect the photoresistor one leg to pin 0, and pin to +5V
Connect a resistor (around 10k is a good value, higher
values gives higher readings) from pin 0 to GND. (see appendix of arduino notebook page 37 for schematics).

----------------------------------------------------
          Laser
 +3.3  o---->---o GND

           PhotoR     10K
 +5    o---/\/\/--.--/\/\/---o GND
                  |
 Pin 0 o-----------

----------------------------------------------------
*/

// Analog pin.
int lightPin = 0;

void setup() {
    Serial.begin(9600);
}

void loop() {
   // Write the value of the photoresistor to the serial monitor.
   Serial.println(analogRead(lightPin));
   delay(100); // Short delay for faster response to light.
}
