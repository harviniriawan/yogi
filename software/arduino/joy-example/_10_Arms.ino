//***********************************
//Definition of arm movements
//***********************************

//mov1 = raise left arm
void mov1()
{
  //perform movement
  while(pos3 != pos3min) {
    pos3 -= 1;
    pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos3 < pos3min) {
      pos3 = pos3min;
    }
  }
  delay(100);
  while(pos3 != pos3max) {
    pos3 += 1;
    pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos3 > pos3max) {
      pos3 = pos3max;
    }
  }
}


//mov2 = raise right arm
void mov2()
{
  //perform movement
  while(pos1 != pos1max) {
    pos1 += 1;
    pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos1 > pos1max) {
      pos1 = pos1max;
    }
  }
  delay(100);
  while(pos1 != pos1min) {
    pos1 -= 1;
    pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos1 < pos1min) {
      pos1 = pos1min;
    }
  }
}


//mov3 = raise both arms
void mov3()
{
  //perform movement
  while((pos1 != pos1max)||(pos3 != pos3min)) {
    pos3 -= 1;
    pos1 += 1;
    pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
    pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos3 < pos3min) {
      pos3 = pos3min;
    }
    if (pos1 > pos1max) {
      pos1 = pos1max;
    }
  }
  delay(100);
  while((pos1 != pos1min)||(pos3 != pos3max)) {
    pos3 += 1;
    pos1 -= 1;
    pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));;
    pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos3 > pos3max) {
      pos3 = pos3max;
    }
    if (pos1 < pos1min) {
      pos1 = pos1min;
    }
  }
}


//mov4 = null
void mov4()
{  
  for(int k = 0; k < 3 ; k++) {
  //perform movement
  while((pos5 != pos5min + 40)) {
    pos5 -= 1;
    pwm.setPWM(4, 0, map(pos5, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos5 < pos5min + 40) {
      pos5 = pos5min + 40;
    }
  }
  while((pos5 != pos5max - 40)) {
    pos5 += 1;
    pwm.setPWM(4, 0, map(pos5, 0, 180, SERVOMIN, SERVOMAX));;
    delay(100/vel);
    if (pos5 > pos5max - 40) {
      pos5 = pos5max - 40;
    }
  }
  }

  while((pos5 != 77)) {
    pos5 -= 1;
    pwm.setPWM(4, 0, map(pos5, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos5 < 77) {
      pos5 = 77;
    }
  }  
}


//mov5 = swinging both arms open
void mov5()
{
    for(int k = 0; k < 3 ; k++) {
  //perform movement
  while((pos1 != pos1max)||(pos3 != pos3min)) {
    pos3 -= 1;
    pos1 += 1;
    pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));
    pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos3 < pos3min) {
      pos3 = pos3min;
    }
    if (pos1 > pos1max) {
      pos1 = pos1max;
    }
  }
  delay(100);
  while((pos1 != pos1min)||(pos3 != pos3max)) {
    pos3 += 1;
    pos1 -= 1;
    pwm.setPWM(2, 0, map(pos3, 0, 180, SERVOMIN, SERVOMAX));;
    pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos3 > pos3max) {
      pos3 = pos3max;
    }
    if (pos1 < pos1min) {
      pos1 = pos1min;
    }
  }
}
}


//mov6 = swing both arms in front
void mov6()
{
    //perform movement
    for(int k = 0; k < 3 ; k++) {
      while((pos2 != pos2min)&& (pos4!= pos4max)) {
        pos2 -= 1;
        pos4 += 1;
        pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 < pos2min) {
          pos2 = pos2min;
        }
        if (pos4 > pos4max) {
          pos4 = pos4max;
        }
      }
      while((pos2 != pos2max)&& (pos4!= pos4min)) {
        pos2 += 1;
        pos4 -= 1;
        pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 > pos2max) {
          pos2 = pos2max;
        }
        if (pos4 < pos4min) {
          pos4 = pos4min;
        }
      }
    }
      while((pos2 != 40) && (pos4!= 130)) {
        pos2 -= 1;
        pos4 += 1;
        pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 < pos2min) {
          pos2 = pos2min;
        }
        if (pos4 > pos4max) {
          pos4 = pos4max;
        }
      }
}


//mov7 = swing both arms in front
void mov7()
{
    //perform movement
    for(int k = 0; k < 3 ; k++) {
      while((pos2 != pos2min)&& (pos4!= pos4min)) {
        pos2 -= 1;
        pos4 -= 1;
        pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 < pos2min) {
          pos2 = pos2min;
        }
        if (pos4 < pos4min) {
          pos4 = pos4min;
        }
      }
      while((pos2 != pos2max)&& (pos4!= pos4max)) {
        pos2 += 1;
        pos4 += 1;
        pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 > pos2max) {
          pos2 = pos2max;
        }
        if (pos4 > pos4max) {
          pos4 = pos4max;
        }
      }
    }
      while((pos2 != 40) && (pos4!= 130)) {
        pos2 -= 1;
        pos4 -= 1;
        pwm.setPWM(3, 0, map(pos4, 0, 180, SERVOMIN, SERVOMAX));
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 < pos2min) {
          pos2 = pos2min;
        }
        if (pos4 < pos4min) {
          pos4 = pos4max;
        }
      }
}


//mov8 = turn arms
void mov8()
{
 for(int k = 0; k < 3 ; k++) {
  //perform movement
  while((pos6 != pos6min)) {
    pos6 -= 1;
    pwm.setPWM(5, 0, map(pos6, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos6 < pos6min) {
      pos6 = pos6min;
    }
  }
  while((pos6 != pos6max)) {
    pos6 += 1;
    pwm.setPWM(5, 0, map(pos6, 0, 180, SERVOMIN, SERVOMAX));;
    delay(100/vel);
    if (pos6 > pos6max) {
      pos6 = pos6max;
    }
  }
  }

  while((pos6 != 40)) {
    pos6 -= 1;
    pwm.setPWM(5, 0, map(pos6, 0, 180, SERVOMIN, SERVOMAX));
    delay(100/vel);
    if (pos6 < 40) {
      pos6 = 40;
    }
  }
  
}


//mov9 = wave
void mov9()
{  
    //perform movement
    //raise arm
    while(pos2!= pos2max) {
        pos2 += 1;
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 > pos2max) {
          pos2 = pos2max;
        }
      }
    //wave
    for(int k = 1; k < 5 ; k++) {
      while(pos1 != (pos1max - 50)) {
        pos1 += 1;
        pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
      }
      while(pos1 != pos1min) {
        pos1 -= 1;
        pwm.setPWM(0, 0, map(pos1, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
      }
    }
    while(pos2 != 40) {
        pos2 -= 1;
        pwm.setPWM(1, 0, map(pos2, 0, 180, SERVOMIN, SERVOMAX));
        delay(100/vel);
        if (pos2 < pos2min) {
          pos2 = pos2min;
        }
    }  
}
