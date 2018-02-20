#include "pince.h"

#define debugPin 22
#define bouton 30
#define rotorButton 36


int val=10;    // variable to read the value from the analog pin 
int valRotor = 90;
int rotorAngle = 0;
bool boutonTrigger = false;
CDF_pince pince(8,9,33);   


void setup() 
{   
	Serial.begin(115200);
	Serial.print("Début");
} 

void loop() 
{  
/*	if(digitalRead(rotorButton)){
    while(digitalRead(rotorButton));
    if(rotorAngle == 0){
      rotorAngle = 1;
      pince.rot(1);
    }else if(rotorAngle==1){
      rotorAngle = 2;
      pince.rot(90);
    }else{
      rotorAngle = 0;
      pince.rot(179);
    }
	}
  
	if(digitalRead(bouton)){
		boutonTrigger = !boutonTrigger;
		while(digitalRead(bouton));

		if(boutonTrigger){
			pince.autoGrab();
		}else{
			pince.relax();
		}
	}
} 
*/
      pince.rot(90);
      pince.autoGrab();
      delay(2000);
      pince.relax();
      delay(2000);

}











  /*if (Serial.available() > 0) {
    // read the incoming byte:
    
    val = atoi(Serial.readString().c_str());
    if(i){
      pince.autoGrab();
      Serial.println("grab");
      i = false;
    }else{
      pince.relax();
      Serial.println("relax");
      i = true;
    } 
    }*/

