// Display temperature and time on LCD
#include "LCD.h"

void LCDsetup(LiquidCrystal_I2C lcd)
{
  lcd.init(); // initialize the lcd 
  // Print a message to the LCD.
  lcd.backlight();
}

void SendDataToLCD(float temperature, int Time, LiquidCrystal_I2C lcd)
{
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print("*c");
  lcd.setCursor(0,1);
  lcd.print("Time: ");
  lcd.print(Time);
  lcd.print("s");
}