//Stepper output info
#define targetPOT A0
#define sensorPOT A1
#define pwmINPUT 3
#define PUL 6
#define DIR 9   

#define pulseWidth 20  // microseconds
#define stepsPerRev 200
#define rangeOfRev .9
#define gearRatio 15.3
#define maxGearboxRPM 20
#define max_e 100

int currentPos;
int targetPos;
int e;
int i;

int maxCCW =  gearRatio * stepsPerRev / 2;
int maxCW = - gearRatio * stepsPerRev / 2;


void PULSE(float RPM, int dir) {
  float stepFreq = RPM / 60 * stepsPerRev * gearRatio;
  int cycleWidth = (1.0 / stepFreq) * 1000000;
  digitalWrite(DIR, dir);
  digitalWrite(PUL, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(PUL, LOW);
  delayMicroseconds(cycleWidth - pulseWidth);

}

void setup() {
  // put your setup code here, to run once:
  //pinMode(targetPOT, INPUT);
  pinMode(sensorPOT, INPUT);
  pinMode(PUL, OUTPUT);
  pinMode(DIR, OUTPUT);
  //Serial.begin(115200);
}

void posControl(){}

void loop() {
  //*
  // put your main code here, to run repeatedly:
  //targetPos = map(analogRead(targetPOT), 0, 1023, maxCW, maxCCW); // use potentiometer for target position
  targetPos = rangeOfRev * map(pulseIn(pwmINPUT,HIGH),1000,2000, maxCW, maxCCW); // use pwm from RC for target position
  currentPos = map(analogRead(sensorPOT), 0, 1023, maxCW, maxCCW);

  e = targetPos - currentPos;
  if (abs(e) > max_e) { //if the abs of error is above allowable error
    i = max_e / 2;      //set i to half the max allowable error
    
    while (i > 0) {
      if (e > max_e) {
        boolean dir = 1;
        PULSE(maxGearboxRPM, dir);
        //Serial.print(dir);
      }
      if (e < -max_e) {
        boolean dir = 0;
        PULSE(maxGearboxRPM, dir);
        //Serial.print(dir);

      }
      i -= 1;

    }

    
  }//*/
        /*
      Serial.print(maxCW);
      Serial.print('\t');
      Serial.print(maxCCW);
      Serial.print('\t');///
      Serial.print(analogRead(A0));
      Serial.print('\t');
      Serial.print(analogRead(A1));
      Serial.print('\t');
      Serial.print(targetPos);
      Serial.print('\t');
      Serial.println(currentPos);///
      //delay(10); //extra long delay for testing, remove before final version
      //*/
     // delay(100);

}
