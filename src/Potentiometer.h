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

    String DroneColor() {
        
        potentiometerValue = analogRead(potentiometerPin);
        if (abs(potentiometerValue - previousPotentiometerValue) > tolerance)
        {
            //Serial.println(potentiometerValue);
            previousPotentiometerValue = potentiometerValue;
        }
        
        if(previousPotentiometerValue < 400) {
            return "BLACK";
        }else if (previousPotentiometerValue > 400 && previousPotentiometerValue < 800) {
            return "BLUE";
        }else if (previousPotentiometerValue > 800 && previousPotentiometerValue < 1200) {
            return "BEIGE";
        }else if (previousPotentiometerValue > 1200 && previousPotentiometerValue < 1600) {
            return "BROWN";
        }else if (previousPotentiometerValue > 1600 && previousPotentiometerValue < 2000) {
            return "BISQUE";
        }else if (previousPotentiometerValue > 2000 && previousPotentiometerValue < 2400) {
            return "DARKGREEN";
        }else if (previousPotentiometerValue > 2400 && previousPotentiometerValue < 2800) {
            return "DARKSALMON";
        }else if (previousPotentiometerValue > 2800 && previousPotentiometerValue < 3200) {
            return "COLAR";
        }else if (previousPotentiometerValue > 3200 && previousPotentiometerValue < 3600) {
            return "BLUEVIOLET";
        }else if (previousPotentiometerValue > 3600 && previousPotentiometerValue < 4000) {
            return "DARKRED";
        }
        return "no color";    
    }
};