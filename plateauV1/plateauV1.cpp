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

void CDF_plateau::parcours(double x,double y){
  this->distance = sqrt(pow(x-this->x,2) + pow(y-this->y,2));
  double angle = atan2(x-this->x,y-this->y)*180/PI - this->angle;
  if(angle > 180)
    angle = -angle+180;
  if(angle < -180)
    angle = -angle-180;
  this->angle = atan2(x-this->x,y-this->y)*180/PI;
  this->asservisement.rotation(angle);
  this->asservisement.stop();
  while(this->asservisement.avancement(true) <= distance){
    Serial.print("Avant");Serial.println((capteurAvant.TestCapteur());
    Serial.print("Gauche");Serial.println((capteurGauche.TestCapteur());
    Serial.print("Droite");Serial.println((capteurDroite.TestCapteur());
    Serial.println(" ");
  }
  this->asservisement.stop();
  this->x = x;
  this->y = y;
}

void CDF_plateau::Contournement(){

}
void CDF_plateau::Dectection(){
  /*  if(capteurAvant.TestCapteur()){
      if(!capteurDroite.TestCapteur()){
        this->asservisement.rotation(90);
        delay(200);
        while(capteurGauche.TestCapteur())
          this->asservisement.avancement(true);
      }
      if(!capteurGauche.TestCapteur()){
        this->asservisement.rotation(-90);
        delay(200);
        while(capteurDroite.TestCapteur())
          this->asservisement.avancement(true);
      }
      else
        this->asservisement.stop();
        delay(1000);
    }
    else{
      if(capteurDroite.TestCapteur()){
          this->asservisement.diff -= 1000;
          this->decalage = -2000;
      }
      else if(capteurGauche.TestCapteur()){
          this->decalage = +2000;
          this->asservisement.diff += 1000;
      }
      else if(this->decalage != 0){
        if(this->decalage > 0){
          this->decalage--;
          this->asservisement.diff--;
        }
        else{
          this->decalage++;
          this->asservisement.diff++;
        }
      }
      else{
        Serial.print("Goooo");
      }
    }*/
}

void CDF_plateau::Trigger(){
  while(!digitalRead(this->pinTrigger)){
    Serial.print("Trigger : ");
    Serial.println(digitalRead(this->pinTrigger));
    delay(200);
  }
}
