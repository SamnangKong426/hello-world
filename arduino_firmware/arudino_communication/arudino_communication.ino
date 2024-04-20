#include <ros.h>
#include <std_msgs/Int32.h>

int encoderPinLeft=2;
int encoderPinRight=3;

int IN3 = 9;
int IN4 = 10;
int ENA = 11;

int ENB = 5;
int IN1 = 6;
int IN2 = 7;

volatile unsigned long totalPulsesLeft = 0;
volatile unsigned long totalPulsesRight = 0;

int motorVelocityLeft = 0;
int motorVelocityRight = 0;

ros::NodeHandle nh;

void callBackFunctionMotorLeft(const std_msgs::Int32 &motorVelocityLeftROS) {
    motorVelocityLeft = motorVelocityLeftROS.data;
}

void callBackFunctionMotorRight(const std_msgs::Int32 &motorVelocityRightROS) {
    motorVelocityRight = motorVelocityRightROS.data;
}

std_msgs::Int32 leftEncoderROS;
ros::Publisher leftEncoderROSPublisher("left _encoder_pulses", &leftEncoderROS);

std_msgs::Int32 rightEncoderROS;
ros::Publisher rightEncoderROSPublisher("right _encoder_pulses", &rightEncoderROS);

ros::Subscriber<std_msgs::Int32> leftMotorROSSubscriber("left_motor_velocity", &callBackFunctionMotorLeft);
ros::Subscriber<std_msgs::Int32> rightMotorROSSubscriber("right_motor_velocity", &callBackFunctionMotorRight);

void interruptFunctionLeft() {
    totalPulsesLeft++;
}

void interruptFunctionRight() {
    totalPulsesRight++;
}

void setup() {

    pinMode(encoderPinLeft, INPUT);
    pinMode(encoderPinRight, INPUT);

    attachInterrupt(digitalPinToInterrupt(encoderPinLeft), interruptFunctionLeft, RISING);
    attachInterrupt(digitalPinToInterrupt(encoderPinRight), interruptFunctionRight, RISING);

    pinMode(ENA, OUTPUT);
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);

    pinMode(ENB, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    leftEncoderROS.data = totalPulsesLeft;
    rightEncoderROS.data = totalPulsesRight;
    leftEncoderROSPublisher.publish(&leftEncoderROS);
    rightEncoderROSPublisher.publish(&rightEncoderROS);

    nh.getHardware()->setBaud(9600);
    nh.initNode();

    nh.advertise(leftEncoderROSPublisher);
    nh.advertise(rightEncoderROSPublisher);

    nh.subscribe(leftMotorROSSubscriber);
    nh.subscribe(rightMotorROSSubscriber);
}

void loop() {
    nh.spinOnce();

    analogWrite(ENA, motorVelocityLeft);
    analogWrite(ENB, motorVelocityRight);

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);

    leftEncoderROS.data = totalPulsesLeft;
    rightEncoderROS.data = totalPulsesRight;
    leftEncoderROSPublisher.publish(&leftEncoderROS);
    rightEncoderROSPublisher.publish(&rightEncoderROS);

    delay(5);
}
