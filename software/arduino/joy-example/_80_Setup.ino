//************************
//Initialise Arduino
//************************
void setup()
{
  //initialisation of displays (setting intensity, zeroing displays)
  lc.shutdown(0, false);
  lc.setIntensity(0, 1);
  lc.clearDisplay(0);
  lc.shutdown(1, false);
  lc.setIntensity(1, 1);
  lc.clearDisplay(1);
  lc.shutdown(2, false);
  lc.setIntensity(2, 1);
  lc.clearDisplay(2);
  lc.shutdown(3, false);
  lc.setIntensity(3, 1);
  lc.clearDisplay(3);
  lc.shutdown(4, false);
  lc.setIntensity(4, 1);
  lc.clearDisplay(4);

  pwm.begin();
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

  //keep face sleeping during startup (until connected to wifi)
  fac8();

  //initialisation of arms
  pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
  pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
  pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
  pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
  pwm.setPWM(4, 0, map(pos5, 0, 180, SERVOMIN, SERVOMAX));
  pwm.setPWM(5, 0, map(pos6, 0, 180, SERVOMIN, SERVOMAX));

  //output pins for motors
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  
  //initialise serial communications
  Serial.begin(9600);
  esp8266.begin(19200);

  sendData("AT+RST\r\n", 2000, DEBUG); //reset module
  sendData("AT+CWMODE=1\r\n", 1000, DEBUG); //set station mode
  sendData("AT+CWJAP=\"XXXXX\",\"YYYYY\"\r\n", 2000, DEBUG);   //connect to wifi network
  while (!esp8266.find("OK")) { //wait for connection
  }
  
  sendData("AT+CIPMUX=1\r\n", 1000, DEBUG); //configures for multiplie connections
  sendData("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // start web server on port 80
  sendData("AT+CIFSR\r\n", 1000, DEBUG); //show IP address

  //activate cheery face after connecting to wifi
  fac1();

  //initialise timer
  tempo0 = millis();
}
