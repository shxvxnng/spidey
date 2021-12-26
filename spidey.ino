/*
Code for Spidey - Bluetooth controlled Quadruped robot
By Shivanng Puri
Link: https://github.com/shxvxnng/spidey
*/

//============Bluetooth Setup============
#define BLYNK_USE_DIRECT_CONNECT
#include <SoftwareSerial.h>
SoftwareSerial DebugSerial(2, 3); // RX, TX
#define BLYNK_PRINT DebugSerial
#include <BlynkSimpleSerialBLE.h>
// ======================================Add Auth token Here=================================
char auth[] = "YourAuthToken";
// ======================================

//=============Servo Setup===============
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

struct joint{
  struct pos{
    int adr;
    int min_pos;
    int max_pos;
    int rest_pos;
  }A, B, C;
}Fr, Fl, Br, Bl;
// ======================================


void setup()
{
  //==========Servo Declaration==========
  pwm.begin();
  pwm.setPWMFreq(1000);
  Wire.setClock(400000);

  Fr.A.adr = 11;  Fr.B.adr = 3;  Fr.C.adr = 7;
  Fl.A.adr = 8;  Fl.B.adr = 0;  Fl.C.adr = 4;
  Br.A.adr = 9;  Br.B.adr = 1;  Br.C.adr = 5;
  Bl.A.adr = 10;  Bl.B.adr = 2;  Bl.C.adr = 6;
  //=====================================
  // Debug console
  DebugSerial.begin(9600);
  DebugSerial.println("Waiting for connections...");

  Serial.begin(38400); //baud rate of HC-05 is 38400
  Blynk.begin(Serial, auth);
}

void loop()
{
  //servo sweep loop
  for (uint8_t pin=0; pin<16; pin++) {
    pwm.setPWM(pin, 4096, 0);       // turns pin fully on
    delay(100);
    pwm.setPWM(pin, 0, 4096);       // turns pin fully off
  }
  
  Blynk.run();
}
