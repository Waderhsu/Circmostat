#ifndef LCD_H
#define LCD_H

#include "Arduino.h"
#include <LiquidCrystal_I2C.h> 

void LCDsetup(LiquidCrystal_I2C lcd);
void SendDataToLCD(float temperature, int Time, LiquidCrystal_I2C lcd);

#endif