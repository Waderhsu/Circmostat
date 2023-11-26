#ifndef HEATER_CONTROL_H
#define HEATER_CONTROL_H

#include "Arduino.h"
#include <OneWire.h> 
#include <DallasTemperature.h> 

void Sensorsetup(DallasTemperature sensors);
void Relaysetup(byte relay_pin);
float TemperatureMaintain(byte relay_pin, DallasTemperature sensors, float Tem_setting[]);

#endif