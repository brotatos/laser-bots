/*
    Name:           Daniel Kauffman
    Project:        Laser Bots
    Organization:   Cal Poly Robotics Club
    Term:           Fall 2014
*/

/* Useful commands:

   $ screen /dev/<arduino-port> <baud-rate> # for connecting for serial coms
*/


#include <Servo.h>


Servo servoLeft;
Servo servoRight;
int targetPin = 5;
int laserPin = 9;
int servoLeftPin = 10;
int servoRightPin = 11;
unsigned long laserTimer = 0;
unsigned long servoTimer = 0;


void setup()
{
    Serial.begin(9600);
    pinMode(laserPin, OUTPUT);
    servoLeft.attach(servoLeftPin);
    servoRight.attach(servoRightPin);
    servoLeft.write(95);
    servoRight.write(96);
}




void loop()
{
    int photoResistor = analogRead(targetPin);
    char input = '\0';
    
    Serial.println(photoResistor);
    delay(200);
    
    // deactivate laser if it is on and 2 seconds have elapsed
    if (digitalRead(laserPin) == HIGH)
    {
        if (millis() - laserTimer > 2000)
        {
            digitalWrite(laserPin, LOW);
        }
    }
    
    // stop servos if 100 ms have elapsed
    if (servoTimer != 0)
    {
        if (millis() - servoTimer > 100)
        {
            stopServo();
        }
    }
    
    if (Serial.available() > 0)
    {
        input = Serial.read();
        
        // activate laser and start timer if space key is pressed
        if (input == ' ')
        {
            laserTimer = millis();
            digitalWrite(laserPin, HIGH);
        }
        // start servos and timer
        else
        {
            servoTimer = millis();
            startServo(input);
        }
        
        emptyStream();
    }
}




void startServo(char dir)
{
    switch (dir)
    {
        // go forward
        case 'w':   servoLeft.write(180);
                    servoRight.write(0);
                    break;
        // go backward
        case 's':   servoLeft.write(0);
                    servoRight.write(180);
                    break;
        // turn left
        case 'a':   servoLeft.write(0);
                    servoRight.write(0);
                    break;
        // turn right
        case 'd':   servoLeft.write(180);
                    servoRight.write(180);
                    break;
    }
}




void stopServo()
{
    servoLeft.write(95);
    servoRight.write(96); 
}




void emptyStream()
{
    while (Serial.available() > 0)
    {
        Serial.read(); 
    }
}
