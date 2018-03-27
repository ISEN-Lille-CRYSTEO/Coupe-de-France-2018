#include "plateauV1.h"

CDF_plateau::CDF_plateau(int pinTrigger){
  this->pinTrigger = pinTrigger;
  pinMode(this->pinTrigger,INPUT);
  this->capteurDroite = CDF_capteur(33,35);
	this->capteurGauche = CDF_capteur(41,43);
	this->capteurAvant = CDF_capteur(37,39);
  //this->capteurArriere = CDF_capteur(45,47);
	//constructeur par défaut
}

void CDF_plateau::parcours(double x,double y,bool detour){
  this->distance = sqrt(pow(x-this->x,2) + pow(y-this->y,2));
  this->decalage = 0;
  double angle = atan2(x-this->x,y-this->y)*180/PI - this->angle;
  if(angle > 180)
    angle = -angle+180;
  if(angle < -180)
    angle = -angle-180;
  this->angle = atan2(x-this->x,y-this->y)*180/PI;
  this->asservisement.rotation(angle);
  this->asservisement.stop();
  while(this->asservisement.avancement(true) <= distance){
    this->Dectection();
  }
  this->asservisement.stop();
  if(detour){
    this->x = x;
    this->y = y;
  }
}

void CDF_plateau::Contournement(int sens){
  if(this->decalage > 3){
    delay(1000);
    this->x = 0;
    this->y = 0;
    this->decalage = 0;
  }
  this->decalage =+ 0.25;
  this->asservisement.stop();
  delay(250);
  if(sens)
    this->parcours(this->x,this->y + this->decalage ,false);
  else
    this->parcours(this->x,this->y - this->decalage ,false);
}

void CDF_plateau::Dectection(){
  if(capteurAvant.TestCapteur(350.0))
      if(!capteurDroite.TestCapteur(200.0))
        this->Contournement(0);
      else if(!capteurGauche.TestCapteur(200.0))
        this->Contournement(1);
      else
        delay(1000);
}

void CDF_plateau::Trigger(){
  while(!digitalRead(this->pinTrigger)){
    Serial.print("Trigger : ");
    Serial.println(digitalRead(this->pinTrigger));
    delay(200);
  }
}
