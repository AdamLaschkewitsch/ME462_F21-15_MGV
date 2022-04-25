#define pulseWidth 20// microseconds
#define cycleWidth 1000 //microseconds

byte PotReading;
float onTime;
float offTime;

byte POT() {
  PotReading = map(analogRead(A1),0,1023,0,255);
  return PotReading;
}
/*
void PULSE(int PIN, float cycleWidth) {
  digitalWrite(PIN, HIGH);
  delayMicroseconds(pulseWidth);
  digitalWrite(PIN, LOW);
  delayMicroseconds(cycleWidth - pulseWidth);
}//*/
void PWM(int PIN, float dutyCycle) {
  onTime= dutyCycle*cycleWidth;
  offTime= cycleWidth - onTime;
    //Serial.print(onTime);
  //  Serial.print('\t');
   // Serial.println(offTime);
  digitalWrite(PIN, HIGH);
  delayMicroseconds(onTime);
  digitalWrite(PIN, LOW);
  delayMicroseconds(offTime);
  }

void setup() {
  // put your setup code here, to run once:
pinMode(A1, INPUT);
pinMode(3,OUTPUT);
pinMode(5,OUTPUT);
pinMode(6,OUTPUT);

//Serial.begin(115200);
//digitalWrite(3,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
 // float dutyCycle=POT()/255.;
//Serial.print(POT());
   // Serial.print('\t');

//  Serial.println(dutyCycle);
  //PWM(3,dutyCycle);
 // Serial.println(PWM);
  //delay(20);
  byte pot = map(POT(),0,255,1,254);
  analogWrite(3,pot);
  analogWrite(5,map(pot,0,255,255,0));
  analogWrite(6,pot/2);
delay(10);
}
