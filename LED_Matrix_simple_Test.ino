//We always have to include the library
#include "LedControl.h"

/*
 Now we need a LedControl to work with.
 ***** These pin numbers will probably not work with your hardware *****
 pin 12 is connected to the DataIn 
 pin 11 is connected to the CLK 
 pin 10 is connected to LOAD 
 We have only a single MAX72XX.
 */
LedControl lc=LedControl(12,11,10,1);

/* we always wait a bit between updates of the display */
unsigned long delaytime=1000;

void setup() {
  /*
   The MAX72XX is in power-saving mode on startup,
   we have to do a wakeup call
   */
  lc.shutdown(0,false);
  /* Set the brightness to a medium values */
  lc.setIntensity(0,8);
  /* and clear the display */
  lc.clearDisplay(0);
  Serial.begin(9600);
}



void loop() { 

  for(int col=0;col<8;col++) {
    for(int row=7;row>-1;row--) {
      delay(delaytime);
      lc.setLed(0,row,col,true);
      delay(delaytime);
      lc.setLed(0,row,col,false);
      Serial.print(row);
      Serial.print(", ");
      Serial.println(col);
    }
  }
}

int getRow(int role, int val){
  return false;
}
