#include "plateauV1.h"

CDF_plateau::CDF_plateau(int pinTrigger){
  //=== Déclaration de la Pile ===
  this->List = new vector<Point>;
  //=== Déclaration du Trigger ===
  this->pinTrigger = pinTrigger;
  pinMode(this->pinTrigger,INPUT);
  //=== Déclaration des capteur ===
  this->capteurDroite = CDF_capteur(33,35);
	this->capteurGauche = CDF_capteur(41,43);
	this->capteurAvant  = CDF_capteur(37,39);
}

void CDF_plateau::parcours(Point A){
  //=== On rajoute le Point dans la List ===
  this->List.push_back(A);
}

void CDF_plateau::Lancement(){
  // Le roboot attent le signal..
  this->Trigger();
  //=== Tant que ma List des point n'est pas vide ===
  while(!this->List.empty()){
    //=== j'avance a mon premier point de ma List ===
    this->direction(&this->List.begin());
    //=== je calcule la distance qui me reste a faire ===
    this->distance = sqrt(pow(&this->List.begin().x - this->A.x,2) + pow(&this->List.begin().y - this->A.y,2));
    //=== j'avance jusqu'a être a la distance shoutaie ===
    while(this->asservisement.avancement(true) <= this->distance){
      //=== je regarde mes capteur ===
      this->Dectection();
    }
    //=== j'écrase mon premier point de la Liste ===
    this->List.erase(this->List.begin());
    //=== Assignation de les point x et y
    this->x += this->asservisement.avancement(true) * cos(this->angle);
    this->y += this->asservisement.avancement(true) * sin(this->angle);
    //=== je reset mes valeur d'asservisement ===
    this->asservisement.stop();
  }
}

void CDF_plateau::Contournement(int sens){
  //=== Assignation de les point x et y
  this->A.x += this->asservisement.avancement(true) * cos(this->angle);
  this->A.y += this->asservisement.avancement(true) * sin(this->angle);
  //=== je reset mes valeur d'asservisement ===
  this->asservisement.stop();
  if(sens)
    this->ajout(this->A.x,this->A.y + 0.25);
  else
    this->ajout(this->A.x,this->A.y - 0.25);
  //=== j'avance a mon premier point de ma List ===
  this->direction(&this->List.begin());
  //=== je calcule la distance qui me reste a faire ===
  this->distance = sqrt(pow(&this->List.begin().x - this->A.x,2) + pow(&this->List.begin().y - this->A.y,2));
}

void CDF_plateau::direction(Point B){
  //=== je reset mes valeur d'asservisement ===
  this->asservisement.stop();
  //=== je calcule l'angle a effectuer ===
  double angle = atan2(this->B.x - this->A.x ,this->B.y - this->y)*180/PI - this->angle;
  if(angle > 180)
    angle = -angle+180;
  if(angle < -180)
    angle = -angle-180;
  //=== Mon roboot tourne sur lui même ===
  this->asservisement.rotation(angle);
  //=== je calcule l'angle ou regarde mon roboot, et je retient ===
  this->angle = atan2(this->B.x - this->A.x ,this->B.y - this->A.y)*180/PI;
  //=== je reset mes valeur d'asservisement ===
  this->asservisement.stop();
}

void CDF_plateau::Dectection(){
  //=== je test mon capteur de devant a 35cm ===
  if(capteurAvant.TestCapteur(350.0)){
      this->asservisement.stop();
      //=== je test mon capteur Droite à 20cm ===
      if(!capteurDroite.TestCapteur(200.0))
        this->Contournement(0);
      //=== Si non je test mon capteur Gauche à 20cm ===
      else if(!capteurGauche.TestCapteur(200.0))
        this->Contournement(1);
      else
        delay(10000);
  }
}

void CDF_plateau::Trigger(){
  //=== je test si mon capteur Trigger est active
  while(!digitalRead(this->pinTrigger)){
    Serial.print("Trigger : ");
    Serial.println(digitalRead(this->pinTrigger));
    delay(200);
  }
}
