// rosrun rosserial_python serial_node.py /dev/ttyUSB0

#include <AFMotor.h>
#include <ros.h>
#include <geometry_msgs/Twist.h>


// Initail motors pin
AF_DCMotor motor1(1, MOTOR12_1KHZ);
AF_DCMotor motor2(2, MOTOR12_1KHZ);
AF_DCMotor motor3(3, MOTOR34_1KHZ);
AF_DCMotor motor4(4, MOTOR34_1KHZ);


// ros nodehandle
ros::NodeHandle  nh;


void motor_cb( const geometry_msgs::Twist& cmd_msg){ 

  v_x= cmd_msg.linear.x;
  v_y = cmd_msg.linear.y;
  omega = cmd_msg.angular.z;

  Serial.print("Vx: ");
  Serial.print(v_x);
  Serial.print("\tVy: ");
  Serial.print(v_y);
  Serial.print("\tOmega: ");
  Serial.println(omega);
  
  kinematic(v_x, v_y, omega);
//  delay(5000);
  digitalWrite(13, HIGH-digitalRead(13));  //toggle led  
//  kinematic(0, 0, 0);
}


ros::Subscriber<geometry_msgs::Twist> sub("car_robot/cmd_vel", motor_cb);

void setup(){
  
  Serial.begin(9600);
  nh.initNode();
  nh.subscribe(sub);

//   motor1.setSpeed(255);
//   motor1.run(FORWARD);
//   motor2.setSpeed(255);
//   motor2.run(FORWARD);
//   motor3.setSpeed(255);
//   motor3.run(FORWARD);
//   motor4.setSpeed(255);
//   motor4.run(FORWARD);
//
//   delay(2000);
//
//   motor1.setSpeed(0);
//   motor2.setSpeed(0);
//   motor3.setSpeed(0);
//   motor4.setSpeed(0);
  
}

void loop(){
  nh.spinOnce();
  delay(1);
}

void kinematic(float v_x, float v_y, float omega) {

//  Vx = [0, 255]
//  Vy = [0, 255]
//  Omega = [-30.6, 30.6]
  
  float M[4];
  
  M[0] = (v_x - v_y + (lx + ly) * omega) * 1 / r;
  M[1] = (v_x + v_y + (lx + ly) * omega) * 1 / r;
  M[2] = (v_x - v_y - (lx + ly) * omega) * 1 / r;
  M[3] = (v_x + v_y - (lx + ly) * omega) * 1 / r;


  setMotorSpeeds(M[0], M[1], M[2], M[3]);
}

void setMotorSpeeds(float speed1, float speed2, float speed3, float speed4) {

  motor1.setSpeed(abs(speed1));
  if (speed1 > 0) {
    //  motor1.setSpeed(255);
     motor1.run(FORWARD);
  }
  else {
    // motor1.setSpeed(255); 
    motor1.run(BACKWARD);
  }

  motor2.setSpeed(abs(speed2));
  if (speed2 > 0) {
    // motor2.setSpeed(255); 
    motor2.run(FORWARD);
  }
  else {
    // motor2.setSpeed(255); 
    motor2.run(BACKWARD);
  }

  motor3.setSpeed(abs(speed3));
  if (speed3 > 0) {
    // motor3.setSpeed(255); 
    motor3.run(FORWARD);
  }
  else {
    // motor3.setSpeed(255);
    motor3.run(BACKWARD);
  }

  motor4.setSpeed(abs(speed4));
  if (speed4 > 0){
    // motor4.setSpeed(255); 
    motor4.run(FORWARD);
  }
  else {
    // motor4.setSpeed(255); 
    motor4.run(BACKWARD);
  }
}
