#include <Arduino.h>
#include "AsyncUDP.h"

class Potentiometer
{
public:
    int potentiometerPin;
    int potentiometerValue;
    int previousPotentiometerValue = 0;
    int tolerance = 150;
    

    //potentiometer constructor
    Potentiometer(int potentiometerPin)
    {
        this->potentiometerPin = potentiometerPin;
        pinMode(potentiometerPin, INPUT);
    }

    /*
    // Potentiometer loop
    void loop()
    {
        potentiometerValue = analogRead(potentiometerPin);
        if (abs(potentiometerValue - previousPotentiometerValue) > tolerance)
        {
            Serial.println(potentiometerValue);
            previousPotentiometerValue = potentiometerValue;
        }
    }
    */

};