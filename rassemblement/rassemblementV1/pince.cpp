#include "pince.h"

CDF_pince::CDF_pince(int pinPince, int pinRotor, int pinCapteur){
  this->pinCapteur = pinCapteur;
  pinMode(pinCapteur, INPUT);
  pince.attach(pinPince);
  rotor.attach(pinRotor); 
  pince.write(degrePince);
  rotor.write(degreRotor);
}


int CDF_pince::grab(int degre){
  if(degre<MaxPince && degre > MinPince){
    this->degrePince = degre;
  }else{
    return 1;
  }
  this->pince.write(this->degrePince);
  return 0;
}

int CDF_pince::autoGrab(){
	while(!digitalRead(pinCapteur) && degrePince > MinPince){
	  	degrePince--;
  		pince.write(degrePince);
  		delay(8);
	}
  degrePince--;
  pince.write(degrePince);
}

int CDF_pince::relax(){
	this->degrePince = MaxPince;
  	pince.write(degrePince);

}

int CDF_pince::rot(int degre){
  if(degre<180 && degre > 0){
    this->degreRotor = degre;
  }else{
    return 1;
  }
  this->rotor.write(this->degreRotor);
  return 0;
}

int CDF_pince::getPinceAngle(){
  return  pince.read();
}

bool CDF_pince::SomeThingTaken() const{
	return digitalRead(pinCapteur);
}







