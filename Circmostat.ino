#include "BLE_connect.h"
#include "Heater_control.h"
#include "LCD.h"

#define DQ_Pin 26
#define relay_pin 4

LiquidCrystal_I2C lcd(0x27,16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display
String device_name = "Circmostat";
OneWire oneWire(DQ_Pin);
DallasTemperature sensors(&oneWire);
String message = "";
bool DeviceON = false;
float Tem_setting[2] = {59.0, 61.0};
float Tem_now = 25.0;
int HeatingTime = 0;        // How much time(sec) has the heating time gone through?
int stage = 1;
int testingtime = 0;
int OnOff;

void TimeCheck(){
  if(stage == 1 && HeatingTime == 900){
    HeatingTime = 0;
    stage = 2;
    Tem_setting[0] = 94;
    Tem_setting[1] = 96;
  }else if(stage == 2 && HeatingTime == 60){    // end
    HeatingTime = 0;
    stage = 3;
  }else{          // count the time
    HeatingTime++;
  }
}

bool ONorOFF(int messagelength){
  if(messagelength == 4){     // if message == "on"
    DeviceON = true;
    //Serial.print("Device on");
  }else if(messagelength == 5){     // if message == "off"
    DeviceON = false;
    //Serial.print("Device off");
  }
  return DeviceON;
}

void setup() {
  Serial.begin(115200);
  BLEsetup(device_name);
  Sensorsetup(sensors);
  Relaysetup(relay_pin);
  LCDsetup(lcd);
}

void loop() {
  sensors.requestTemperatures();
  Tem_now = sensors.getTempCByIndex(0);
  // read message from APP(on/off) and determine whether to start heating
  message = BLEread(message);
  if (Serial.available()) {
    OnOff = Serial.read();
  }
  if(ONorOFF(message.length())|| OnOff == 'O'){
    Tem_now = TemperatureMaintain(relay_pin, sensors, Tem_setting);
  }
  
  if(Tem_now >= Tem_setting[1]- 0.5 && Tem_now <= Tem_setting[0]+ 0.5){
    TimeCheck();
  }

  if(testingtime%10 == 0){
    Serial.print("Temperatures --> ");
    Serial.println(Tem_now);
    // Serial.print("Time --> ");
    // Serial.println(HeatingTime);
  }

  testingtime++;
  delay(880);
  // send data(temperature & time) to APP. each delay 20
  BLEwrite("stage");
  BLEwrite(String(stage));
  BLEwrite("tem");
  BLEwrite(String(Tem_now));
  BLEwrite("time");
  BLEwrite(String(HeatingTime));

  // Display temperature and time on LCD
  SendDataToLCD(Tem_now,  HeatingTime, lcd);
}
