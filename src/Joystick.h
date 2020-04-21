#include <Arduino.h>
#include "AsyncUDP.h"

class Joystick
{
public:
    int joystickPinX;
    int joystickPinY;
    int joystickValueX;
    int joystickValueY;
    int previousJoystickValueX = 0;
    int previousJoystickValueY = 0;
    int joystickButtonPin = 13;
    int tolerance = 200;
    AsyncUDP Judp;

    //joystick constructor
    Joystick(int joystickPinX, int joystickPinY)
    {
        this->joystickPinX = joystickPinX;
        this->joystickPinY = joystickPinY;
        pinMode(joystickPinX, INPUT);
        pinMode(joystickPinY, INPUT);
        pinMode(joystickButtonPin, INPUT_PULLUP);
    }

    String JoystickMove() {
        joystickValueX = analogRead(joystickPinX);
        joystickValueY = analogRead(joystickPinY);

        //only update if bigger than tolerance
        if (abs(joystickValueX - previousJoystickValueX) > tolerance ||
            abs(joystickValueY - previousJoystickValueY) > tolerance) 
        {
        //Serial.print(map(analogRead(pinX), 0, 4095, -100, 100));
        Serial.print("X: ");
        Serial.print(previousJoystickValueX);
        Serial.print(" : ");
        Serial.print("Y: ");
        Serial.println(previousJoystickValueY);
        //Serial.println(map(analogRead(pinY), 0, 4095, 100, -100));
        previousJoystickValueX = analogRead(joystickPinX);
        previousJoystickValueY = analogRead(joystickPinY);
        }

        //if clicked on joystick initiate pixel
        if (digitalRead(joystickButtonPin) == LOW) {
            Serial.println("CLICKED ON");
            return "init";
        }
        //pixel moveup
        else if (previousJoystickValueY > 3500){
            return "moveup";
        }
        //pixel movedown
        else if (previousJoystickValueY < 1500){
            return "movedown";
        }
        //pixel move right
        else if (previousJoystickValueX < 600){
            return "moveright";
        }
        //pixel move left
        else if (previousJoystickValueX > 2000){
            return "moveleft";
        }
        return "0";
    }
};

