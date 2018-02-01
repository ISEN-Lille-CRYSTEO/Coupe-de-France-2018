#include "pince.h"

#define debugPin 22
#define bouton 30
#define potar A2


int val=10;    // variable to read the value from the analog pin 
int valRotor = 90;
bool boutonTrigger = false;
CDF_pince pince(9,11,22);   


void setup() 
{   
	pinMode(debugPin, INPUT);
	pinMode(bouton, INPUT);

	Serial.begin(9600);
	Serial.print("Début");
} 

void loop() 
{  
	valRotor = analogRead(potar);
	valRotor = map(valRotor, 0,1024, 1,179);
	pince.rot(valRotor);

	if(digitalRead(bouton)){
		boutonTrigger = !boutonTrigger;
		do{
			;
		}while(digitalRead(bouton));

		if(boutonTrigger){
			pince.autoGrab();
		}else{
			pince.relax();
		}
	}
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

