#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150
#define SERVOMAX  600
#define USMIN  600
#define USMAX  2400
#define SERVO_FREQ 50

uint8_t servonum = 0;

// ==================

// #define BLYNK_USE_DIRECT_CONNECT

// #include <SoftwareSerial.h>
// SoftwareSerial DebugSerial(2, 3); // RX, TX

// #define BLYNK_PRINT DebugSerial
// #include <BlynkSimpleSerialBLE.h>

// char auth[] = "Blynk Auth Token";

const int servo_pin[4][3] = { {8, 0, 4}, {11, 3, 7}, {10, 2, 6},{9, 1, 5} };

void setup() {
  Serial.begin(9600);
  Serial.println("Servo test!");

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(SERVO_FREQ);

    leg_write(0, 150, 90, 90);
    delay(1000);
    leg_write(1, 30, 60, 60);
    delay(1000);
    leg_write(2, 30, 60, 60);
    delay(1000);
    leg_write(3, 150, 90, 90);
    delay(2000);

   stand();

  // ====================

  // DebugSerial.begin(9600);

  // DebugSerial.println("Waiting for connections...");

  // Serial.begin(9600);
  // Blynk.begin(Serial, auth);
  //This not working because the sketch pauses at Blynk.begin() if the serial port is not responding
}

void loop() {
  // Walking forward
  extend(0);
  flex(3);
  extend(1);
  flex(2);


// Jumping code -

//    for(int i = 0; i <= 30; i++){
//      leg_write(0, 150, 90 - i, 90);
//      leg_write(1, 30, 60 + i, 60);
//      leg_write(2, 30, 60 + i, 60);
//      leg_write(3, 150, 90 - i, 90);
//      delay (10);
//    }
//    delay(1000);
//
//    for(int i = 30; i >= 0; i--){
//      leg_write(0, 150, 90 - i, 90);
//      leg_write(1, 30, 60 + i, 60);
//      leg_write(2, 30, 60 + i, 60);
//      leg_write(3, 150, 90 - i, 90);
//      delay (10);
//    }
//    delay(1000);
//    for(int leg = 0; leg < 4; leg++){
//      for(int i = 60; i <= 120; i++){
//        leg_write(leg, i, 120, 120);
//        delay(10);
//      }
//      delay(1000);
//    }
//    for(int leg = 0; leg < 4; leg++){
//      for(int i = 120; i >= 60; i--){
//        leg_write(leg, i, 120, 120);
//        delay(10);
//      }
//    }

   
}

void leg_write(int leg, float alpha, float beta, float gamma){
  alpha = alpha*10 + USMIN;
  beta = beta*10 + USMIN;
  gamma = gamma*10 + USMIN;

  pwm.writeMicroseconds(servo_pin[leg][0], alpha);
  pwm.writeMicroseconds(servo_pin[leg][2], gamma);
  pwm.writeMicroseconds(servo_pin[leg][1], beta);
}

void servo_write(int joint, int theta){
  int phi = (210 - theta)/2;
  phi = phi*10 + USMIN;
  theta = theta*10 + USMIN;
  if (joint == 2){
    for(int i = 0; i < 4; i++){
      pwm.writeMicroseconds(servo_pin[i][joint], theta);
      delay(10);
    }
  }
  else{
  pwm.writeMicroseconds(servo_pin[0][joint], theta);
  delay(10);
  pwm.writeMicroseconds(servo_pin[1][joint], phi);
  delay(10);
  pwm.writeMicroseconds(servo_pin[2][joint], phi);
  delay(10);
  pwm.writeMicroseconds(servo_pin[3][joint], theta);
  delay(10);
  }
}

void extend(int leg){
  if (leg == 1 || leg == 2){
    for(int i = 30; i <= 90; i++){
    leg_write(leg, i, 90, 90);
    delay(10);
  }
  delay(1000);
  for (int i = 90; i>= 30; i--){
    leg_write(leg, 90, i, i);
    delay(10);
  }
  delay(1000);
  for(int i = 90; i >= 30; i--){
    leg_write(leg, i, 30, 30);
    delay(10);
  }
  delay(1000);
  for (int i = 30; i<= 90; i++){
    leg_write(leg, 30, i, i);
    delay(10);
  }
  delay(1000);
  }
  else{
      for(int i = 150; i >= 90; i--){
      leg_write(leg, i, 90, 90);
      delay(10);
    }
    delay(1000);
    for (int i = 90; i<= 150; i++){
      leg_write(leg, 90, i, i + 10);
      delay(10);
    }
    delay(1000);
    for(int i = 90; i <= 150; i++){
      leg_write(leg, i, 150, 160);
      delay(10);
    }
    delay(1000);
    for (int i = 150; i>= 90; i--){
      leg_write(leg, 150, i, i + 10);
      delay(10);
    }
    delay(1000);

//    for(int i = 90; i <= 150; i++){
//      leg_write(leg, i, 150, 150);
//      delay(10);
//    }
    delay(1000);
  }
}

void flex(int leg){
  if(leg == 1 || leg == 2){
    for (int i = 60; i>= 30; i--){
    leg_write(leg, 30, i, i);
    delay(10);
  }
  delay(1000);
  for(int i = 30; i <= 90; i++){
    leg_write(leg, i, 30, 30);
    delay(10);
  }
  delay(1000);
  for (int i = 30; i<= 60; i++){
    leg_write(leg, 90, i, i);
    delay(10);
  }
  delay(1000);
  for(int i = 90; i >= 30; i--){
    leg_write(leg, i, 60, 60);
    delay(10);
  }
  delay(1000);
  }
  else{
    for (int i = 90; i<= 150; i++){
    leg_write(leg, 150, i, i + 10);
    delay(10);
  }
  delay(1000);
  for(int i = 150; i >= 90; i--){
    leg_write(leg, i, 150, 160);
    delay(10);
  }
  delay(1000);
  for (int i = 150; i>= 90; i--){
    leg_write(leg, 90, i, i + 10);
    delay(10);
  }
  delay(1000);
  for(int i = 90; i <= 150; i++){
    leg_write(leg, i, 90, 100);
    delay(10);
  }
  delay(1000);
    }
}

void stand(){
  servo_write(0, 150);
  delay(100);
  servo_write(1, 60);
  delay(100);
  servo_write(2, 90);
  delay(100);
}
