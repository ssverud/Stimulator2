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
            Serial.println(potentiometerValue);
            previousPotentiometerValue = potentiometerValue;
        }
        
        if(previousPotentiometerValue < 400) {
            return "color 10 10 10";
        }else if (previousPotentiometerValue > 400 && previousPotentiometerValue < 800) {
            return "color 20 20 20";
        }else if (previousPotentiometerValue > 800 && previousPotentiometerValue < 1200) {
            return "color 30 30 30";
        }else if (previousPotentiometerValue > 1200 && previousPotentiometerValue < 1600) {
            return "color 40 40 40";
        }else if (previousPotentiometerValue > 1600 && previousPotentiometerValue < 2000) {
            return "color 50 50 50";
        }else if (previousPotentiometerValue > 2000 && previousPotentiometerValue < 2400) {
            return "color 60 60 60";
        }else if (previousPotentiometerValue > 2400 && previousPotentiometerValue < 2800) {
            return "color 70 70 70";
        }else if (previousPotentiometerValue > 2800 && previousPotentiometerValue < 3200) {
            return "color 80 80 80";
        }else if (previousPotentiometerValue > 3200 && previousPotentiometerValue < 3600) {
            return "color 90 90 90";
        }else if (previousPotentiometerValue > 3600 && previousPotentiometerValue < 4000) {
            return "color 100 100 1000";
        }
        return "no color";    
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