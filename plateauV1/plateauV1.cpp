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
  this->angle(x,y);
  while(this->asservisement.avancement(true) <= this->distance){//j'avance le roboot
    this->Dectection(x,y);//je test mes capteur
  }
  this->asservisement.stop();// je reset les valeur
  this->x = x;// mon roboot est a une cordonée x =
  this->y = y;// mon roboot est a une cordonée y =
}

void CDF_plateau::Contournement(int sens,int x,int y){
  if(this->decalage > 3){
    this->asservisement.stop();// je reset les valeur
    delay(1000);// si je parcours tro loin
    this->decalage = 0; // je revient a ma position initiale et j'attend 1 seconde
  }
  this->decalage =+ 0.25;
  this->distance -= this->asservisement.avancement(true);
  this->x += this->asservisement.avancement(true) * cos(this->angle);// mon roboot est a une cordonée x =
  this->y += this->asservisement.avancement(true) * sin(this->angle);// mon roboot est a une cordonée y =
  if(sens){
    this->parcours(this->x,this->y + this->decalage);
  }
  else{
    this->parcours(this->x,this->y - this->decalage);
  }
  this->angle(x,y);// je tourne vers la bonne direction
  this->distance = sqrt(pow(x-this->x,2) + pow(y-this->y,2));//calcule la distance à faire
  this->asservisement.stop();// je reset les valeur
}

void CDF_plateau::angle(int x,int y){
  this->asservisement.stop();// je reset les valeur
  double angle = atan2(x-this->x,y-this->y)*180/PI - this->angle;// je calcule l'angle a faire
  if(angle >= 359 ||angle <= -359)
    angle = 0;
  if(angle > 180)
    angle = -angle+180;
  if(angle < -180)
    angle = -angle-180;
  this->angle = atan2(x-this->x,y-this->y)*180/PI;// je retient ou mon roboot et orienté
  this->asservisement.rotation(angle);// je tourne mon roboot
  this->asservisement.stop();// je reset les valeur
}

void CDF_plateau::Dectection(int x,int y){
  if(capteurAvant.TestCapteur(350.0))
      if(!capteurDroite.TestCapteur(200.0))
        this->Contournement(0,x,y);
      else if(!capteurGauche.TestCapteur(200.0))
        this->Contournement(1,x,y);
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
