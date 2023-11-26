#ifndef BLE_CONNECT_H
#define BLE_CONNECT_H

#include "Arduino.h"
#include "BluetoothSerial.h"

void BLEsetup(String device_name);
void BLEwrite(String message);
String BLEread(String message);

#endif