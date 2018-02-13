//********************
//Definition of faces
//********************

//change eyes
void display_eyes(byte eye[], int pos) {
  for(int i=0;i<8;i++) {
   lc.setRow(pos,i,eye[i]); //setRow function runs faster than setColumn, thus faces changed using setRow
  } 
}

//change mouth
void display_mouth(byte mouth[]) {
  for(int i=0;i<8;i++) {
    lc.setRow(0,i,mouth[i]); //setRow function runs faster than setColumn, thus faces changed using setRow
    lc.setRow(3,i,mouth[i+8]); //setRow function runs faster than setColumn, thus faces changed using setRow
  }
}

//happy face
void fac1()
{
  face = 1;
  eye_right = 1;
  eye_left = 1;
  mouth = 1;
  blinkset = true;
  display_eyes(eye_neutral_r, 1);
  display_eyes(eye_neutral_l, 2);
  display_mouth(mouth_happy_open);
}

//very happy face
void fac2()
{
  face = 2;
  blinkset = true;
  eye_right = 1;
  eye_left = 1;
  mouth = 2;
  display_eyes(eye_neutral_r, 1);
  display_eyes(eye_neutral_l, 2);
  display_mouth(mouth_happy_open);
}

//sad face
void fac3()
{
  face = 3;
  blinkset = true;
  eye_right = 6;
  eye_left = 6;
  mouth = 3;
  display_eyes(eye_sad_r, 1);
  display_eyes(eye_sad_l, 2);  
  display_mouth(mouth_sad_closed);
}

//very sad face
void fac4()
{
  face = 4;
  blinkset = true;
  eye_right = 6;
  eye_left = 6;
  mouth = 4;
  display_eyes(eye_sad_r, 1);
  display_eyes(eye_sad_l, 2);  
  display_mouth(mouth_sad_open);
}

//face with tongue out
void fac5()
{
  face = 5;
  blinkset = false;
  eye_right = 3;
  eye_left = 3;  
  mouth = 5;
  display_eyes(eye_closed_up_r, 1);  
  display_eyes(eye_closed_up_l, 2);  
  display_mouth(mouth_tongue);
}

//dead face
void fac6()
{
  face = 6;
  blinkset = false;
  eye_right = 5;
  eye_left = 5;
  mouth = 7;
  display_eyes(eye_dead_r, 1);  
  display_eyes(eye_dead_l, 2);  
  display_mouth(mouth_sad_closed);
}

//scared face
void fac7()
{
  face = 7;
  blinkset = true;
  eye_right = 2;
  eye_left = 2;
  mouth = 6;
  display_eyes(eye_wide_r, 1);  
  display_eyes(eye_wide_l, 2);  
  display_mouth(mouth_open);
}

//sleeping face
void fac8()
{
  face = 8;
  blinkset = false;
  eye_right = 4;
  eye_left = 4;  
  mouth = 6;
  display_eyes(eye_closed_down_r, 1);  
  display_eyes(eye_closed_down_l, 2);  
  display_mouth(mouth_open);
}


//confused face
void fac9()
{
  face = 9;
  blinkset = true;
  eye_right = 2;
  eye_left = 1;  
  mouth = 7;
  display_eyes(eye_wide_r, 1);  
  display_eyes(eye_neutral_l, 2);
  display_mouth(mouth_neutral);
}

//bored face
void fac10()
{
  face = 10;
  blinkset = true;
  eye_right = 7;
  eye_left = 7;  
  mouth = 7;
  display_eyes(eye_bored_r, 1);  
  display_eyes(eye_bored_l, 2);
  display_mouth(mouth_neutral);
}

//in love face
void fac11()
{
  face = 11;
  blinkset = true;
  eye_right = 9;
  eye_left = 9;  
  mouth = 1;
  display_eyes(eye_inlove_r, 1);  
  display_eyes(eye_inlove_l, 2);
  display_mouth(mouth_happy_closed);
}

//disgusted face
void fac12()
{
  face = 12;
  blinkset = true;
  eye_right = 1;
  eye_left = 1; 
  mouth = 8;
  display_eyes(eye_neutral_r, 1);  
  display_eyes(eye_neutral_l, 2);
  display_mouth(mouth_disgust);
}

//angry face
void fac13()
{
  face = 13;
  blinkset = true;
  eye_right = 8;
  eye_left = 8;  
  mouth = 3;
  display_eyes(eye_angry_r, 1);  
  display_eyes(eye_angry_l, 2);
  display_mouth(mouth_sad_closed);
}


//Speaking
void fac14()
{
  if ((mouth==1) || (mouth==2) || (mouth==5) || (mouth==7)) {
    display_mouth(mouth_happy_closed);
    delay(100);
    display_mouth(mouth_happy_open);
    delay(100);
    display_mouth(mouth_happy_closed);
    delay(100);
    display_mouth(mouth_neutral);
    delay(100);
    display_mouth(mouth_happy_closed);
    delay(100);
    display_mouth(mouth_happy_open);
    delay(100);
    restore();
  }
  else {
    display_mouth(mouth_sad_closed);
    delay(100);
    display_mouth(mouth_sad_open);
    delay(100);
    display_mouth(mouth_sad_closed);
    delay(100);
    display_mouth(mouth_neutral);
    delay(100);
    display_mouth(mouth_sad_closed);
    delay(100);
    display_mouth(mouth_sad_open);
    delay(100);
    restore();    
  }
}

void restore()
{
        switch (eye_left){
          case 1:
            display_eyes(eye_neutral_l, 2);
            break;
          case 2:
            display_eyes(eye_wide_l, 2);
            break;
          case 3:
            display_eyes(eye_closed_up_l, 2);
            break;        
          case 4:
            display_eyes(eye_closed_down_l, 2);
            break;
          case 5:
            display_eyes(eye_dead_l, 2);
            break;
          case 6:
            display_eyes(eye_sad_l, 2);
            break;
          case 7:
            display_eyes(eye_bored_l, 2);
            break;
          case 8:
            display_eyes(eye_angry_l, 2);
            break;
          case 9:
            display_eyes(eye_inlove_l, 2);
            break;
        }
          
        switch (eye_right){
          case 1:
            display_eyes(eye_neutral_r, 1);
            break;
          case 2:
            display_eyes(eye_wide_r, 1);
            break;
          case 3:
            display_eyes(eye_closed_up_r, 1);
            break;
          case 4:
            display_eyes(eye_closed_down_r, 1);
            break;
          case 5:
            display_eyes(eye_dead_r, 1);
            break;
          case 6:
            display_eyes(eye_sad_r, 1);
            break;
          case 7:
            display_eyes(eye_bored_r, 1);
            break;
          case 8:
            display_eyes(eye_angry_r, 1);
            break;           
          case 9:
            display_eyes(eye_inlove_r, 1);
            break;
        }
      switch (mouth){
        case 1:
          display_mouth(mouth_happy_closed);
          break;
        case 2:
          display_mouth(mouth_happy_open);
          break;
        case 3:
          display_mouth(mouth_sad_closed);
          break;
        case 4:
          display_mouth(mouth_sad_open);
          break;
        case 5:
          display_mouth(mouth_tongue);
          break;
        case 6:
          display_mouth(mouth_open);
          break;
        case 7:
          display_mouth(mouth_neutral);
          break;
        case 8:
          display_mouth(mouth_disgust);
          break;          
          
        }
}
