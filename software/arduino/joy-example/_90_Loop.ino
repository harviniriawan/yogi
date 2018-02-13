//*************************
//Arduino main loop
//*************************
void loop()
{
  int delta = millis() - tempo0;
  if(delta > 3000) {              //if time greater than 10s
    if(blinkset == true) {
      display_eyes(eye_closed_down_r, 2);  //blink eyes
      display_eyes(eye_closed_down_l, 1);  //blink eyes
      delay(200);
      restore();
      tempo0 = millis();
    }
  }
  
  if (esp8266.available())  //check if ESP8266 is receiving data

  {
    if (esp8266.find("+IPD,")) //if data received
    {
      String msg;
      esp8266.find("?"); //run cursor until command found in received message     
      msg = esp8266.readStringUntil(' '); //read string to end of message
      String command = msg.substring(0, 3); //first 3 characters of message = command
      String valueStr = msg.substring(4);   //3 characters = value associated with command
      int value = valueStr.toInt();         //value to integer conversion
      if (DEBUG) {
        Serial.println(command);
        Serial.println(value);
      }
      delay(100);
      
      //************************************************
      //perform actions: move servos to required angles
      //************************************************
      
      //move servo1 to received angle value
      if(command == "sr1") {
         //limit the input angle
         if (value >= pos1max) {
           value = pos1max;
         }
         if (value <= pos1min) {
           value = pos1min;
         }
         //advance to desired angle
         while(pos1 != value) {
           if (pos1 > value) {
             pos1 -= 1;
             pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
           if (pos1 < value) {
             pos1 += 1;
             pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
         }
      }

      //move servo2 to received angle value
      if(command == "sr2") {
         //limit the input angle
         if (value >= pos2max) {
           value = pos2max;
         }
         if (value <= pos2min) {
           value = pos2min;
         }
         while(pos2 != value) {
           if (pos2 > value) {
             pos2 -= 1;
             pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
           if (pos2 < value) {
             pos2 += 1;
             pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
         }   
      }
      
      //move servo3 to received angle value
      if(command == "sr3") {
         //limit the input angle
         value = 180 - value;
         if (value >= pos3max) {
           value = pos3max;
         }
         if (value <= pos3min) {
           value = pos3min;
         }
         while(pos3 != value) {
           if (pos3 > value) {
             pos3 -= 1;
             pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
           if (pos3 < value) {
             pos3 += 1;
             pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
         }   
      }
      
      //move servo4 to received angle value
      if(command == "sr4") {
         value = 180 - value;
         //limit the input angle
         if (value >= pos4max) {
           value = pos4max;
         }
         if (value <= pos4min) {
           value = pos4min;
         }        
         while(pos4 != value) {
           if (pos4 > value) {
             pos4 -= 1;
             pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
           if (pos4 < value) {
             pos4 += 1;
             pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
         }       
      }

      //move servo5 to received input angle
      if(command == "sr5") {
         //limit the input angle
         if (value >= pos5max) {
           value = pos5max;
         }
         if (value <= pos5min) {
           value = pos5min;
         }        
         while(pos5 != value) {
           if (pos5 > value) {
             pos5 -= 1;
             pwm.setPWM(4, 0, map(pos5, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
           if (pos5 < value) {
             pos5 += 1;
             pwm.setPWM(4, 0, map(pos5, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
         }       
      }

      //move servo6 to received input angle
      if(command == "sr6") {
         value = 180 - value;
         //limit the input angle
         if (value >= pos6max) {
           value = pos6max;
         }
         if (value <= pos6min) {
           value = pos6min;
         }        
         while(pos6 != value) {
           if (pos6 > value) {
             pos6 -= 1;
             pwm.setPWM(5, 0, map(pos6, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
           if (pos6 < value) {
             pos6 += 1;
             pwm.setPWM(5, 0, map(pos6, 0, 180, SERVOMIN, SERVOMAX));
             delay(100/vel);
           }
         }       
      }


      //****************************
      //perform actions: arms
      //****************************

      if(command == "mov") {

        if(value == 10) {
            mov1(); //mov1 = raise left arm
        }
        if(value == 20) {
            mov2(); //mov2 = raise right arm
        }
        if(value == 30) {
            mov3(); //mov3 = raise both arms
        }
        if(value == 40) {
            mov4(); //mov4 = lower both arms
        }
        if(value == 50) {
            mov5(); //mov5 = swinging both arms open
        }
        if(value == 60) {
            mov6(); //mov6 = swinging both arms to front
        }
        if(value == 70) {
            mov7(); //mov7 = swinging both arms to front
        }
        if(value == 80) {
            mov8(); //mov8 = turning arms
        }        
        if(value == 90) {
            mov9(); //mov9 = wave
        }

      }
      
      //**********************************
      //perform actions: face expressions
      //**********************************

      if(command == "fac") {
        if(value == 10) {
          fac1(); //happy
        }
        if(value == 20) {
          fac2(); //very happy
        }
        if(value == 30) {
          fac3(); //sad
        }
        if(value == 40) {
          fac4(); //very sad
        }
        if(value == 50) {
          fac5(); //tongue out
        }
        if(value == 60) {
          fac6(); //dead
        }
        if(value == 70) {
          fac7(); //scared
        }
        if(value == 80) {
          fac8(); //sleeping
        }
        if(value == 90) {
          fac9(); //confused
        }
        if(value == 100) {
          fac10(); //bored
        }  
        if(value == 110) {
          fac11(); //in love
        }  
        if(value == 120) {
          fac12(); //disgusted
        }  
        if(value == 130) {
          fac13(); //angry
        }
        if(value == 140) {
          fac14(); //speaking
        } 
      }

      if(command == "old") {
        if(value == 10) {
          display_eyes(eye_neutral_r, 1);
          eye_right = 1;
        }
        if(value == 20) {
          display_eyes(eye_wide_r, 1);
          eye_right = 2;
        }
        if(value == 30) {
          display_eyes(eye_closed_up_r, 1);
          eye_right = 3;
        }
        if(value == 40) {
          display_eyes(eye_closed_down_r, 1);
          eye_right = 4;
        }
        if(value == 50) {
          display_eyes(eye_dead_r, 1);
          eye_right = 5;
        }
        if(value == 60) {
          display_eyes(eye_sad_r, 1);
          eye_right = 6;
        }
        if(value == 70) {
          display_eyes(eye_bored_r, 1);
          eye_right = 7;
        }
        if(value == 80) {
          display_eyes(eye_angry_r, 1);
          eye_right = 8;
        }
        if(value == 90) {
          display_eyes(eye_inlove_r, 1);
          eye_right = 9;
        }
      }
      
      if(command == "ole") {
        if(value == 10) {
          display_eyes(eye_neutral_l, 2);
          eye_left = 1;
        }
        if(value == 20) {
          display_eyes(eye_wide_l, 2);
          eye_left = 2;
        }
        if(value == 30) {
          display_eyes(eye_closed_up_l, 2);
          eye_left = 3;          
        }
        if(value == 40) {
          display_eyes(eye_closed_down_l, 2);
          eye_left = 4;          
        }
        if(value == 50) {
          display_eyes(eye_dead_l, 2);
          eye_left = 5;          
        }
        if(value == 60) {
          display_eyes(eye_sad_l, 2);
          eye_left = 6;          
        }
        if(value == 70) {
          display_eyes(eye_bored_l, 2);
          eye_left = 7;          
        }
        if(value == 80) {
          display_eyes(eye_angry_l, 2);
          eye_left = 8;          
        }                        
        if(value == 90) {
          display_eyes(eye_inlove_l, 2);
          eye_left = 9;          
        }
      }
      
      if(command == "boc") {
        if(value == 10) {
          display_boca(mouth_happy_closed);
          boca = 1;
        }
        if(value == 20) {
          display_boca(mouth_happy_open);
          boca = 2;
        }
        if(value == 30) {
          display_boca(mouth_sad_closed);
          boca = 3;          
        }
        if(value == 40) {
          display_boca(mouth_sad_open);
          boca = 4;          
        }
        if(value == 50) {
          display_boca(mouth_tongue);
          boca = 5;          
        }
        if(value == 60) {
          display_boca(mouth_open);
          boca = 6;          
        }
        if(value == 70) {
          display_boca(mouth_neutral);
          boca = 7;          
        }
        if(value == 80) {
          display_boca(mouth_neutral);
          boca = 8;          
        }
        if(value == 90) {
          display_boca(mouth_disgust);
          boca = 9;          
        }

        
      }
      //***************************************
      //perform action: change speed
      //***************************************

      if(command == "vel") {
        vel = value;
      }


      //**********************************
      //moving DC motors
      //**********************************

      if(command == "mot") {
        if(value == 10) {
          mot1(); //move forward
        }
        if(value == 20) {
          mot2(); //move right
        }
        if(value == 30) {
          mot3(); //move left
        }
        if(value == 40) {
          mot4(); //move backward
        }
      }

      
    }
  }
}
