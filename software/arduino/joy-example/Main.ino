// Robô da Alegria v2.0
//By Igor Fonseca Albuquerque
//   Thiago Ferrauche
//   Yhan Christian
//   Paulo de Azevedo Jr.

//****************************
//Initialise global variables
//****************************

//include libraries
#include <SoftwareSerial.h>
#include <Servo.h>
#include "LedControl.h"

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
#define SERVOMIN  150 // this is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX  600 // this is the 'maximum' pulse length count (out of 4096)

LedControl lc = LedControl(9,10,11,4); //Pins 9 (DIN), 10 (CLK), 11 (CS), 4 displays to be controlled
SoftwareSerial esp8266(5, 4); //RX pin 5, TX pin 4

//motor pins definition
const int motor1Pin1 = 2;
const int motor1Pin2 = 3;
const int motor2Pin1 = 7;
const int motor2Pin2 = 6;
//motor speed setting
int motorSpeed = 255; //motor speed (PWM)

//definition of variables
#define DEBUG true //display messages exchanged between the ESP8266 and the Arduino on the serial port

int pos1 = 30; //current angle of servo 1
int pos2 = 40; //current angle of servo 2
int pos3 = 135; //current angle of servo 3
int pos4 = 130; //current angle of servo 4
int pos5 = 77; //current angle of servo 5
int pos6 = 40; //current angle of servo 6
int vel = 10; //speed of servos (100 -> 90º in 1s)(1 -> 90º in 1s)
int pos1min = 20; //minimum angle of servo 1
int pos2min = 10; //minimum angle of servo 2
int pos3min = 42; //minimum angle of servo 3
int pos4min = 10; //minimum angle of servo 4
int pos5min = 30; //minimum angle of servo 5
int pos6min = 26; //minimum angle of servo 6
int pos1max = 115; //maximum angle of servo 1
int pos2max = 170; //maximum angle of servo 2
int pos3max = 136; //maximum angle of servo 3
int pos4max = 170; //maximum angle of servo 4
int pos5max = 150; //maximum angle of servo 5
int pos6max = 50; //maximum angle of servo 6
int face; //current face number
int right_eye; //current right eye number
int left_eye; //current left eye number
int mouth; //current mouth number
boolean blinkset; //to set whether or not to blink
unsigned long tempo0; //time to blink
