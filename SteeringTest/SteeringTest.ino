#include <PPMReader.h>

// Initialize a PPMReader on digital pin 3 with 8 expected channels.
#define PPMpin 3 //must be capable of interupts, which is pin 2 and 3 on nano
#define channelAmount 8

//Stepper output info
#define PUL 6
#define DIR 8
#define pulseWidth 20  // microseconds
#define stepsPerRotation 200
#define rangeOfRotation 1

PPMReader ppm(PPMpin, channelAmount);
float maxCCW = 15.3 * stepsPerRotation * rangeOfRotation / 2;
float maxCW = -15.3 * stepsPerRotation * rangeOfRotation / 2;

void setup() {
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(13, OUTPUT);
  Serial.begin(115200);
}
//*
void PULSE(int Step_Hz, int dir) {
  float cycleWidth = (1.0 / Step_Hz) * 1000000;

  digitalWrite(DIR, dir);
  digitalWrite(PUL, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(PUL, LOW);
  delayMicroseconds(cycleWidth - pulseWidth);
}
//*/

void ROTATE() {
  unsigned ch3 = ppm.rawChannelValue(3); //Left Throttle joystick
  unsigned ch5 = ppm.rawChannelValue(5); //right 3 pole switch

  int Step_Hz = map(ch3, 1000, 2000, 25, 5000);
  int dir;
  if (ch5 > 1750) { //if 3 pole switch is down
    dir = 1;
    PULSE(Step_Hz, dir);

  } else if (ch5 < 1250) { //if 3 pole switch is up
    dir = 0;
    PULSE(Step_Hz, dir);

  } else { ////if 3 pole switch is in the middle

  }
}
/*
void posControl() {
    float i = 0;
    unsigned ch4;
    float targetPos;
    float e;
    ch4 = ppm.rawChannelValue(4); //Left yaw joystick
    targetPos = map(ch4, 1000, 2000, maxCW, maxCCW);
    e = targetPos - i;
    if (e > 0) {
      PULSE(1000, 1);
      i += 1;
    }
    if (e < 0) {
      PULSE(1000, 0);
      i -= 1;
    }
  }//*/
  void loop() {
    unsigned ch7 = ppm.rawChannelValue(7); //Left 2 pole switch
    while (ch7 < 1250) { // if the 2 pole switch is down, rotate constantly
      ch7 = ppm.rawChannelValue(7); //update ch7
      ROTATE();
    }
    if (ch7 > 1750) {
      float i = 0;
      unsigned ch4;
      float targetPos;
      float e;
      while (ch7 > 1750) { // if the 2 pole switch is up, go to position
        ch7 = ppm.rawChannelValue(7); //update ch7
        ch4 = ppm.rawChannelValue(4); //Left yaw joystick
        targetPos = map(ch4, 1000, 2000, maxCW, maxCCW);
        e = targetPos - i;
        if (e > 0) {
          PULSE(1000, 1);
          i += 1;
        }
        if (e < 0) {
          PULSE(1000, 0);
          i -= 1;
        }
        /*
          Serial.print(targetPos);
          Serial.print('\t');
          Serial.println(i);
          Serial.print('\t');
          Serial.print(e);//*/
      }
    }
    if ( ch7 > 1250 && ch7 < 1750) {
      digitalWrite(13, HIGH);
      delay(200);
      digitalWrite(13, LOW);
      delay(200);
    }
  }
