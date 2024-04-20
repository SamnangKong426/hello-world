#include <ros.h>
#include <geometry_msgs/Twist.h>

// Define motor pins
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor2Pin1 = 4;
const int motor2Pin2 = 5;

const int motor1EnablePin = 6; // PWM pin for motor 1 speed control
const int motor2EnablePin = 7; // PWM pin for motor 2 speed control


// kinematic
float lx = 12;
float ly = 13;
float r = 3;
float v_x = 0, v_y = 0, omega = 0;

// ros nodehandle
ros::NodeHandle nh;

void motor_cb(const geometry_msgs::Twist& cmd_msg) {
  v_x = cmd_msg.linear.x;
  v_y = cmd_msg.linear.y;
  omega = cmd_msg.angular.z;

  Serial.print("Vx: ");
  Serial.print(v_x);
  Serial.print("\tVy: ");
  Serial.print(v_y);
  Serial.print("\tOmega: ");
  Serial.println(omega);

  kinematic(v_x, v_y, omega);
}

ros::Subscriber<geometry_msgs::Twist> sub("car_robot/cmd_vel", motor_cb);

void setup() {
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  Serial.begin(9600);
  nh.initNode();
  nh.subscribe(sub);
}

void loop() {
  nh.spinOnce();
  delay(1);
}

void kinematic(float v_x, float v_y, float omega) {
  float M[2];

  M[0] = (v_x - v_y + (lx + ly) * omega) * 1 / r;
  M[1] = (v_x + v_y + (lx + ly) * omega) * 1 / r;

  setMotorSpeeds(M[0], M[1]);
}

void setMotorSpeeds(float speed1, float speed2) {
  // Motor 1
  if (speed1 >= 0) {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);
    analogWrite(motor1EnablePin, speed1);
  } else {
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, HIGH);
    analogWrite(motor1EnablePin, -speed1);
  }

  // Motor 2
  if (speed2 >= 0) {
    digitalWrite(motor2Pin1, HIGH);
    digitalWrite(motor2Pin2, LOW);
    analogWrite(motor2EnablePin, speed2);
  } else {
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, HIGH);
    analogWrite(motor2EnablePin, -speed2);
  }
}
