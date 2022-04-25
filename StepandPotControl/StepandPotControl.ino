//Stepper output info
#define POT A0
#define PUL 6
#define DIR 8

#define pulseWidth 20  // microseconds
#define stepsPerRev 200
#define rangeOfRev 1
#define gearRatio 15.3
#define maxGearboxRPM 25
#define max_e 5

float maxCCW =  gearRatio * stepsPerRev * rangeOfRev / 2;
float maxCW = - gearRatio * stepsPerRev * rangeOfRev / 2;
float currentPos;
float targetPos;
float e;
int maxPulseFreq = stepsPerRev * 10;
int i;

float mapfloat(long x, long in_min, long in_max, long out_min, long out_max) {
  return (float)(x - in_min) * (out_max - out_min) / (float)(in_max - in_min) + out_min;
}

void PULSE(float RPM, int dir) {

  float stepFreq = RPM / 60 * stepsPerRev * gearRatio;

  float cycleWidth = (1.0 / stepFreq) * 1000000;
  digitalWrite(DIR, dir);
  digitalWrite(PUL, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(PUL, LOW);
  delayMicroseconds(cycleWidth - pulseWidth);

}

void setup() {
  // put your setup code here, to run once:
  pinMode(POT, INPUT);
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  //Serial.begin(115200);
  int currretPos = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  targetPos = mapfloat(analogRead(POT), 0, 1023, maxCW, maxCCW);
  e = targetPos - currentPos;
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
      i -= 1;
      /*
      Serial.print(maxCW);
      Serial.print('\t');
      Serial.print(maxCCW);
      Serial.print('\t');
      Serial.print(analogRead(A0));
      Serial.print('\t');
      Serial.print(targetPos);
      Serial.print('\t');
      Serial.println(currentPos);//*/
    }
  }
}
