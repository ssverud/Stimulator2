#include <Arduino.h>
#include "WiFi.h"
#include "AsyncUDP.h"
#include "Joystick.h"
#include "Potentiometer.h"
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x3F,16,2);  // set the LCD address 
                                    // to 0x3F for a 16 chars and 1 line display

const char *ssid = "AndroidAPC910";
const char *password = "fnsa6355";

AsyncUDP udp;
AsyncUDP Judp;

Joystick joystick(36, 39);
Potentiometer potentiometer(34);


void setup()
{
    // initialize the lcd 
    lcd.init();

    // Print a message to the LCD.
    
    lcd.backlight();
    lcd.setCursor(0,0);
    lcd.print("Press joystick");
    

    Serial.begin(9600);



    //Connection to pxlserver
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    


    if (WiFi.waitForConnectResult() != WL_CONNECTED)
    {
        Serial.println("WiFi Failed");
        while (1)
        {
            delay(1000);
        }
    }
        
    if (udp.listen(7007))
    {
        Serial.print("UDP Listening on IP: ");
        Serial.println(WiFi.localIP());
        udp.onPacket([](AsyncUDPPacket packet) {
            Serial.print("UDP Packet Type: ");
            Serial.print(packet.isBroadcast() ? "Broadcast" : packet.isMulticast() ? "Multicast" : "Unicast");
            Serial.print(", From: ");
            Serial.print(packet.remoteIP());
            Serial.print(":");
            Serial.print(packet.remotePort());
            Serial.print(", To: ");
            Serial.print(packet.localIP());
            Serial.print(":");
            Serial.print(packet.localPort());
            Serial.print(", Length: ");
            Serial.print(packet.length());
            Serial.print(", Data: ");
            Serial.write(packet.data(), packet.length());
            Serial.println();
            
            //reply to the client
            packet.printf("Got %u bytes of data", packet.length());
            Serial.print("state: ");

            // convertion of packetdata to string
            String s((char*)packet.data());
            s = s.substring(0, packet.length()); 
            s.trim();
            lcd.clear();
            lcd.print(s);

       Serial.println();
        });
    }
}

void loop()
{
    // Potentiometer color change   
    String s = potentiometer.DroneColor();
    int sLength = s.length();
    char charArrayPotentiometer[sLength + 1];
    for(int i=0 ; i < sLength ; i++ ) {
            charArrayPotentiometer[i] = s[i];
    }

    udp.writeTo((const uint8_t *)charArrayPotentiometer, s.length(), IPAddress(192, 168, 43, 255), 7000);

    //joystick
    String j = joystick.JoystickMove();
    int jLength = j.length();
    char charArrayJoystick[jLength + 1];
    for(int i=0 ; i < jLength ; i++) {
        charArrayJoystick[i] = j[i];
    }       
    
    Judp.writeTo((const uint8_t *)charArrayJoystick, j.length(), IPAddress(192, 168, 43, 255), 7000);

};