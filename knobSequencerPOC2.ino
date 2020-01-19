//Reference:
//https://tronixstuff.com/2013/10/11/tutorial-arduino-max7219-led-display-driver-ic/
//https://learn.adafruit.com/mcp4725-12-bit-dac-tutorial

//TODO: Add clock, reset and pgm hardware.

#include <LedControl.h>
#include <Wire.h>
#include <Adafruit_MCP4725.h>
#include "pins_arduino.h" // Arduino pre-1.0 needs this

#define semitones 68.25
#define minClock 600
#define clockPin 2
#define programPin 3
#define gate1Pin 13
#define knobPin A0
#//define quantizePin A2

bool quantize, programmedStep;
int thisStep, previousStep, knobRead, knobValue, beat, triggeredOnce;//2 track will include programTrack

int gate[16]{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int cv[16]{0,0,0,0,0,0,0,0.0,0,0,0,0,0,0,0};

unsigned long lastTrig;
//LED position arrays

LedControl lc=LedControl(12,11,10,1);
Adafruit_MCP4725 ch1Voltage;

//for POC, leaving out track 2 and fixing quantize at FALSE for now.
//steps are 1 indexed for ease of reading
void setup() {
  //input pins-knob is analog 0
  pinMode(knobPin, INPUT);
  //interrupts so we don't miss clock or write
  attachInterrupt(digitalPinToInterrupt(clockPin), nextStep, RISING);
  pinMode(programPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(programPin), programStep, FALLING);
  
  //pinMode(quantizePin, INPUT);
  //set up display
  lc.shutdown(0,false);// turn off power saving, enables display
  lc.setIntensity(0,8);// sets brightness (0~15 possible values)
  lc.clearDisplay(0);// clear screen
  
  //gate
  pinMode(gate1Pin, OUTPUT);
  thisStep=0;
  triggeredOnce=0;
  quantize = false;
  //quantize = digitalRead(quantizePin)==HIGH?TRUE:FALSE;//if including quantize switch
  //progmTrack = digitalRead(programPin)==HIGH?2:1;//if using 2nd track
  knobRead = analogRead(knobPin);
  knobValue = quantize?map(knobRead, 0,1024, 0, 4096):(map(knobRead, 0, 1024,0,60)*semitones);
  ch1Voltage.begin(0x62);
  //ch2Voltage.begin(0x63);//if using 2nd track
  Serial.begin(9600);
}

void loop() {
  previousStep=thisStep==0?15:thisStep-1;//calculate previous clock
  lc.setLed(0,7-(thisStep<8?thisStep:thisStep-8),thisStep>7?1:0,true);
  lc.setLed(0,7-(previousStep<8?previousStep:previousStep-8),previousStep>7?1:0,false);
  //single gate version
  if(gate[thisStep]&&!triggeredOnce){
    digitalWrite(gate1Pin, HIGH);
    delay(20);
    digitalWrite(gate1Pin, LOW);
    triggeredOnce=1;
  }
  ch1Voltage.setVoltage(cv[thisStep], false);//send voltage
}

void nextStep(){
  //advance on clock or step button rise
  triggeredOnce=0;
  thisStep=thisStep==15?0:thisStep+1;//increment or reset step
  for (int i=0;i<16;i++){//diagnostic only-okay to remove loop
    Serial.print(gate[i]);
    Serial.print(",");
  }
  Serial.println();
}

void programStep(){
  //set value of gate and trigger for step
  knobRead = analogRead(knobPin);
  knobValue = quantize?map(knobRead, 0,1023, 0, 4096):(map(knobRead, 0, 1023,0,60)*semitones);
  //for 2 track, would need condition and second array set
  gate[thisStep]=1;
  cv[thisStep]=knobValue;
  lc.setLed(0,7-(thisStep<8?thisStep:thisStep-8), thisStep>7?7:6, true);  
}
