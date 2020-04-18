#include <Arduino.h>
#include "WiFi.h"
#include "AsyncUDP.h"
#include "Joystick.h"
#include "Potentiometer.h"

const char *ssid = "AndroidAPC910";
const char *password = "fnsa6355";

AsyncUDP udp;
AsyncUDP Pudp;

Joystick joystick(36, 39);
Potentiometer potentiometer(34);

void setup()
{
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
            /*  Serial.write(packet.data(), packet.length());
            String s((char*)packet.data());
            s = s.substring(0, packet.length()); 
            s.trim();
            // send string to method
            Serial.println(s);
            udp.printf("Received your message!");
        */
       Serial.println();
        });
    }
}

void loop()
{
    
    // Potentiometer
    // potentiometer.loop();

    

    if (true) {
        String s = potentiometer.DroneColor();
        Serial.println(s);
        Serial.println(s.length());

        Pudp.writeTo((const uint8_t *)"'s'" , s.length(), IPAddress(192, 168, 43, 255), 7000);
    }


    /*
    //pxlserver pixel color change
        if (potentiometer.previousPotentiometerValue < 400)
        {
            Pudp.writeTo((const uint8_t *)"color 80 20 50", 14, IPAddress(192, 168, 43, 255), 7000);
        }
        if (potentiometer.previousPotentiometerValue > 400 && potentiometer.previousPotentiometerValue < 800)
        {
            Pudp.writeTo((const uint8_t *)"color 200 200 200", 17, IPAddress(192, 168, 43, 255), 7000);
        }
        if (potentiometer.previousPotentiometerValue > 800 && potentiometer.previousPotentiometerValue < 1200)
        {
            Pudp.writeTo((const uint8_t *)"color 50 50 50", 14, IPAddress(192, 168, 43, 255), 7000);
        }
        if (potentiometer.previousPotentiometerValue > 1200 && potentiometer.previousPotentiometerValue < 1600)
        {
            Pudp.writeTo((const uint8_t *)"color 50 90 60", 14, IPAddress(192, 168, 43, 255), 7000);
        }
        if (potentiometer.previousPotentiometerValue > 1600 && potentiometer.previousPotentiometerValue < 2000)
        {
            Pudp.writeTo((const uint8_t *)"color 100 50 200", 16, IPAddress(192, 168, 43, 255), 7000);
        }
        if (potentiometer.previousPotentiometerValue > 2000 && potentiometer.previousPotentiometerValue < 2400)
        {
            Pudp.writeTo((const uint8_t *)"color 50 200 200", 16, IPAddress(192, 168, 43, 255), 7000);
        }
        if (potentiometer.previousPotentiometerValue > 2400 && potentiometer.previousPotentiometerValue < 2800)
        {
            Pudp.writeTo((const uint8_t *)"color 50 200 100", 16, IPAddress(192, 168, 43, 255), 7000);
        }
        if (potentiometer.previousPotentiometerValue > 3200 && potentiometer.previousPotentiometerValue < 3600)
        {
            Pudp.writeTo((const uint8_t *)"color 20 50 50", 14, IPAddress(192, 168, 43, 255), 7000);
        }
        if (potentiometer.previousPotentiometerValue > 3600 && potentiometer.previousPotentiometerValue < 4000)
        {
            Pudp.writeTo((const uint8_t *)"color 90 100 80", 15, IPAddress(192, 168, 43, 255), 7000);
        }
        */

    //Joystick
    joystick.loop();
};