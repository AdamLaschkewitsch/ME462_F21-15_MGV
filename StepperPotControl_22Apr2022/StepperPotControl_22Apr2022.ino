#include <PPMReader.h>

// Initialize a PPMReader on digital pin 3 with 8 expected channels.
#define PPMpin 3 //must be capable of interupts, which is pin 2 and 3 on nano
#define channelAmount 8

//Stepper output info
#define PUL 6
#define DIR 8
#define pulseWidth 20  // microseconds
#define stepsPerRev 200
#define rangeOfRev 1
#define gearRatio 15.3
#define maxGearboxRPM 25

//---------------------------
//---------------------------

PPMReader ppm(PPMpin, channelAmount);
int maxCCW =  gearRatio * stepsPerRev * rangeOfRev / 2;
int maxCW = - gearRatio * stepsPerRev * rangeOfRev / 2;
int currentPos;
unsigned ch7;
int maxPulseFreq = stepsPerRev * 10;

//---------------------------
//---------------------------

//*
float mapfloat(long x, long in_min, long in_max, long out_min, long out_max)
{
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

//---------------------------

void PULSE(float RPM, int dir) {

  float stepFreq = RPM / 60 * stepsPerRev * gearRatio;

  float cycleWidth = (1.0 / stepFreq) * 1000000;
  digitalWrite(DIR, dir);
  digitalWrite(PUL, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(PUL, LOW);
  delayMicroseconds(cycleWidth - pulseWidth);

}
//*/
//---------------------------

int ROTATE(int currentPos) {
  unsigned ch3 = ppm.rawChannelValue(3); //Left Throttle joystick
  unsigned ch5 = ppm.rawChannelValue(5); //right 3 pole switch

  float RPM = mapfloat(ch3, 1000, 2000, 0, maxGearboxRPM); // min and max gearbox rpm
  if (RPM > 0) {
    if (ch5 > 1750) { //if 3 pole switch is down
      PULSE(RPM, 1);
      currentPos += 1;

    } else if (ch5 < 1250) { //if 3 pole switch is up
      PULSE(RPM, 0);
      currentPos -= 1;

    } else { ////if 3 pole switch is in the middle

    }
    return currentPos;
  }
  else {
  }
}
//*

//---------------------------
/*
int posCONTROL(int Position) {
  int max_e = 50;
  unsigned ch4;
  float targetPos;
  float e;
  int i;
  ch4 = ppm.rawChannelValue(4); //Left yaw joystick
  targetPos = map(ch4, 1000, 2000, maxCW, maxCCW);
  e = targetPos - currentPos;
  //Serial.println(e);
  if (abs(e) > max_e) {
    i = max_e / 2;
    while (i > 0) {
      if (e > max_e) {
        PULSE(maxGearboxRPM, 1);
        currentPos += 1;
      }

      if (e < -max_e) {
        PULSE(maxGearboxRPM, 0);
        currentPos -= 1;
      }
      i-=1;
    }
    
    return currentPos;

  }
}//*/
//---------------------------
//---------------------------

void setup() {
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(A7,INPUT);
  Serial.begin(115200);
}
void loop() {
  ch7 = ppm.rawChannelValue(7); //Left 2 pole switch
  Serial.println(ch7);
  //  currentPos = currentPos % (gearRatio * stepsPerRotation * rangeOfRotation / 2);
  while (ch7 < 1250) { // if the 2 pole switch is down, blink LED
    ch7 = ppm.rawChannelValue(7); //update ch7
    currentPos = ROTATE(currentPos);
    //Serial.println(i);

  }

  while (ch7 > 1750) { // if the 2 pole switch is up, control position
    ch7 = ppm.rawChannelValue(7); //update ch7
   // currentPos = posCONTROL(currentPos);
    // Serial.println(i);

  }

  if ( ch7 > 1250 && ch7 < 1750 || ch7<950) { // if invalid signal is detected, only flash led
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
    delay(200);
    // Serial.println(i);
  }
}