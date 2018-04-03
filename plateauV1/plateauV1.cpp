#include "plateauV1.h"

CDF_plateau::CDF_plateau(int pinTrigger){
  this->pinTrigger = pinTrigger;
  pinMode(this->pinTrigger,INPUT);
  this->capteurDroite = CDF_capteur(33,35);// pinTrigger = 33, pinEcho 35
	this->capteurGauche = CDF_capteur(41,43);// pinTrigger = 41, pinEcho 43
	this->capteurAvant = CDF_capteur(37,39); // pinTrigger = 37, pinEcho 39
  //this->capteurArriere = CDF_capteur(45,47);
	//constructeur par défaut
}

void CDF_plateau::parcours(double x,double y){
  this->distance = sqrt(pow(x-this->x,2) + pow(y-this->y,2));//calcule la distance à faire
  this->decalage = 0;// je remet le décalage du mon roboot a zero
  this->direction(x,y);
  while(this->asservisement.avancement(true) <= this->distance){//j'avance le roboot
    this->Dectection(x,y);//je test mes capteur
  }
  this->asservisement.stop();// je reset les valeur
  this->x = x;// mon roboot est a une cordonée x =
  this->y = y;// mon roboot est a une cordonée y =
}

void CDF_plateau::Contournement(int sens,int x,int y){
  this->x += this->asservisement.avancement(true) * cos(this->angle);// mon roboot est a une cordonée x =
  this->y += this->asservisement.avancement(true) * sin(this->angle);// mon roboot est a une cordonée y =
  this->asservisement.stop();// je reset les valeur
  if(sens)
    this->parcours(this->x,this->y + 0.5);
  else
    this->parcours(this->x,this->y - 0.5);
  this->direction(x,y);// je tourne vers la bonne direction
  this->distance = sqrt(pow(x-this->x,2) + pow(y-this->y,2));//calcule la distance à faire
}

void CDF_plateau::direction(int x,int y){
  this->asservisement.stop();// je reset les valeur
  double angle = atan2(x-this->x,y-this->y)*180/PI - this->angle;// je calcule l'angle a faire
  if(angle > 180)
    angle = -angle+180;
  if(angle < -180)
    angle = -angle-180;
  this->asservisement.rotation(angle);// je tourne mon roboot
  this->angle = atan2(x-this->x,y-this->y)*180/PI;// je retient ou mon roboot et orienté
  this->asservisement.stop();// je reset les valeur
}

void CDF_plateau::Dectection(int x,int y){
  if(capteurAvant.TestCapteur(350.0)){
      this->asservisement.stop();// je reset les valeur
      if(!capteurDroite.TestCapteur(200.0))
        this->Contournement(0,x,y);
      else if(!capteurGauche.TestCapteur(200.0))
        this->Contournement(1,x,y);
      else
        delay(10000);
  }
}

void CDF_plateau::Trigger(){
  while(!digitalRead(this->pinTrigger)){
    Serial.print("Trigger : ");
    Serial.println(digitalRead(this->pinTrigger));
    delay(200);
  }
}
