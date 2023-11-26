// Connect software through Bluetooth
#include "BLE_connect.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

#if !defined(CONFIG_BT_SPP_ENABLED)
#error Serial Bluetooth not available or not enabled. It is only available for the ESP32 chip.
#endif

BluetoothSerial SerialBT;

void BLEsetup(String device_name) {
  SerialBT.begin(device_name); //Bluetooth device name
  Serial.printf("The device with name \"%s\" is started.\nNow you can pair it with Bluetooth!\n", device_name.c_str());
}

void BLEwrite(String message) {

  SerialBT.println(message);

  delay(20);
}

String BLEread(String message){
  String outputmessage = message;

  if (SerialBT.available()) {
    outputmessage = SerialBT.readString();
    Serial.println(outputmessage);
  }

  return outputmessage;
}