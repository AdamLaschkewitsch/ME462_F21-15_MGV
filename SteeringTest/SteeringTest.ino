#include <PPMReader.h>

// Initialize a PPMReader on digital pin 3 with 8 expected channels.
byte PPMpin = 3; //must be capable of interupts, which is pin 2 and 3 on nano
byte channelAmount = 8;
PPMReader ppm(PPMpin, channelAmount);

byte PUL=6;
byte DIR=8;
int pulseWidth = 20;  // microseconds
int millisbetweenSteps = 250; // milliseconds - or try 1000 for slower steps

void setup() {

    pinMode(PUL,OUTPUT);
    pinMode(DIR,OUTPUT);
    Serial.begin(115200);
}
//*
void PULSE(int Step_Hz,int dir){
    float microbetweenSteps=(1.0/Step_Hz)*1000000;
    
    digitalWrite(DIR,dir);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(PUL,LOW);
    delayMicroseconds(microbetweenSteps-pulseWidth);
    //Serial.println(microbetweenSteps);
}
//*/
void loop() {
  //plot channels of PPM
  /*
    // Print latest valid values from all channels
    for (byte channel = 1; channel <= channelAmount; ++channel) {
        //unsigned value = ppm.latestValidChannelValue(channel, 0);]
        unsigned value = ppm.rawChannelValue(channel);
        Serial.print(value);
    if(channel < channelAmount) Serial.print('\t');
    }
    Serial.println();
  delay(20);
  */

unsigned ch3= ppm.rawChannelValue(3); 
unsigned ch7= ppm.rawChannelValue(7);
int Step_Hz = map(ch3,1000,2000,25,5000);
int dir = 0;

if (ch7 > 1500){
  dir = 1;
}

PULSE(Step_Hz,dir);


/*
int Hz_Geared=100;
int Hz_Motor = Hz_Geared*15.3;
float microbetweenSteps=(1.0/Hz_Motor)*1000000;
    
    //digitalWrite(DIR,);
    digitalWrite(PUL,HIGH);
    delayMicroseconds(pulseWidth);
    digitalWrite(PUL,LOW);
    delayMicroseconds(microbetweenSteps);
    */
}
