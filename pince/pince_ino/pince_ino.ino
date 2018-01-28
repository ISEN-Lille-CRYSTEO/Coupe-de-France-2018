#include "pince.h"

#define debugPin 22

int val=10;    // variable to read the value from the analog pin 
bool i = true;
CDF_pince pince(9,11,22);   


void setup() 
{   
    pinMode(debugPin, INPUT);
    Serial.begin(9600);
    Serial.print("BITE");
} 

void loop() 
{  
  
  if (Serial.available() > 0) {
    // read the incoming byte:
    
    val = atoi(Serial.readString().c_str());
    if(i){
      pince.autoGrab();
      Serial.println("BITE grab");
      i = false;
    }else{
      pince.relax();
      Serial.println("BITE relax");
      i = true;
    } 
  }
  
  
  
} 

