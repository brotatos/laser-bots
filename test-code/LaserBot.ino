/*
    Name:           Daniel Kauffman
    Project:        Laser Bots
    Organization:   Cal Poly Robotics Club
    Term:           Fall 2014
*/


#include <Servo.h>


Servo servoLeft;
Servo servoRight;
int laserPin = 9;
int servoLeftPin = 10;
int servoRightPin = 11;
unsigned long laserTimer = 0;
unsigned long servoTimer = 0;
char input = '\0';


void setup()
{
    Serial.begin(9600);
    pinMode(laserPin, OUTPUT);
}




void loop()
{
    if (Serial.available() > 0)
    {
        input = Serial.read();
    
        // deactivate laser if it is on and 2 seconds have elapsed
        if (digitalRead(laserPin) == HIGH)
        {
            if (millis() - laserTimer > 2000)
            {
                digitalWrite(laserPin, LOW);
            }
        }
        // activate laser and start timer if space key is pressed
        else if (input == ' ')
        {
            laserTimer = millis();
            digitalWrite(laserPin, HIGH);
        }
        // stop servos if 100 ms have elapsed
        else if (millis() - servoTimer > 100)
        {
            stopServo();
        }
        // start servos and timer
        else
        {
            servoTimer = millis();
            startServo(input);
        }
    }

    emptyStream();
}




void startServo(char dir)
{
    servoLeft.attach(servoLeftPin);
    servoRight.attach(servoRightPin);
    
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
    servoLeft.detach();
    servoRight.detach();   
}




void emptyStream()
{
    while (Serial.available() > 0)
    {
        Serial.read(); 
    }
}
