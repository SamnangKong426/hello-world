#include <AFMotor.h>
#include <SoftwareSerial.h>

SoftwareSerial bluetoothSerial(9, 10); // RX, TX

// Initial motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);

char command;

float lx = 12;
float ly = 13;
float r = 3;

void setup() {
  bluetoothSerial.begin(9600);  // Set the baud rate to your Bluetooth module.
}

void loop() {
  if (bluetoothSerial.available() > 0) {
    command = bluetoothSerial.read();
    Stop(); // Initialize with motors stopped
    
    switch (command) {
      case 'F':
        kinematic(255, 0.0, 0.0); // Move forward
        break;
      case 'B':
        kinematic(-255, 0.0, 0.0); // Move backward
        break;
      case 'L':
        kinematic(0.0, 255, 0.0); // Turn left
        break;
      case 'R':
        kinematic(0.0, -255, 0.0); // Turn right
        break;
      case 'G':
        kinematic(0.0, 0.0, 255); // Rotate left
        break;
      case 'I':
        kinematic(0.0, 0.0, -255); // Rotate right
        break;
    }
  }
}

void kinematic(float V_x, float V_y, float omega) {
  float M[4];
  
  M[0] = (V_x - V_y + (lx + ly) * omega) * 1 / r;
  M[1] = (V_x + V_y + (lx + ly) * omega) * 1 / r;
  M[3] = (V_x + V_y - (lx + ly) * omega) * 1 / r;
  M[2] = (V_x - V_y - (lx + ly) * omega) * 1 / r;

  setMotorSpeeds(M[0], M[1], M[2], M[3]);
}

void setMotorSpeeds(float speed1, float speed2, float speed3, float speed4) {


  if (speed1 > 0) {
     motor1.setSpeed(255);
     motor1.run(FORWARD);
  }
  else {
    motor1.setSpeed(255); 
    motor1.run(BACKWARD);
  }

  if (speed2 > 0) {
    motor2.setSpeed(255); 
    motor2.run(FORWARD);
  }
  else {
    motor2.setSpeed(255); 
    motor2.run(BACKWARD);
  }

  if (speed3 > 0) {
    motor3.setSpeed(255); 
    motor3.run(FORWARD);
  }
  else {
    motor3.setSpeed(255);
    motor3.run(BACKWARD);
  }

  if (speed4 > 0){
    motor4.setSpeed(255); 
    motor4.run(FORWARD);
  }
  else {
    motor4.setSpeed(255); 
    motor4.run(BACKWARD);
  }
}

void Stop() {
  motor1.setSpeed(0);
  motor2.setSpeed(0); 
  motor3.setSpeed(0); 
  motor4.setSpeed(0); 
}
