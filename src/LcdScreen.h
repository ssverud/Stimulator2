#include <Arduino.h>
#include <LiquidCrystal_I2C.h>
#include <MPU6050_tockn.h>
MPU6050 mpu6050(Wire);
LiquidCrystal_I2C lcd(0x3F,16,1);  // set the LCD address to 0x3F for a 16 chars and 1 line display

// forbindelse til accerometeret på "bagsiden" af LCD display
byte LED_PIN_SDA = 21;
byte LED_PIN_SCL = 22;

