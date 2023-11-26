// Turn on/off the heater to maintain temperature in the range
#include "Heater_control.h"

float Temp_NOW;
float Temp_SET_HIGH = 36.0;
float Temp_SET_LOW = 35.0;

void Sensorsetup(DallasTemperature sensors)
{
  sensors.begin();
}

void Relaysetup(byte relay_pin)
{
  pinMode (relay_pin, OUTPUT);
}

float TemperatureMaintain(byte relay_pin, DallasTemperature sensors, float Tem_setting[]) {
  sensors.requestTemperatures();
  Temp_NOW = sensors.getTempCByIndex(0);

  if(Temp_NOW <= Tem_setting[0]){ //open
    digitalWrite(relay_pin,HIGH);
    //Serial.println("heater on");
  }
  if(Temp_NOW >= Tem_setting[1]){
    digitalWrite(relay_pin,LOW);
    //Serial.println("heater off");
  }
  return Temp_NOW;
}