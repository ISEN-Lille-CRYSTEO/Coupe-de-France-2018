#include "plateauV2.h"

CDF_plateau::CDF_plateau(int pinTrigger){
  //=== Déclaration du Trigger ===
  this->A.x = 0;
  this->A.y = 0;
  this->pinTrigger = pinTrigger;
  this->pince = CDF_pince(8,9,7);
  pinMode(this->pinTrigger,INPUT);
  //=== Déclaration des capteur ===
  this->capteurDroite = CDF_capteur(33,35);
	this->capteurGauche = CDF_capteur(41,43);
	this->capteurAvant  = CDF_capteur(37,39);
}

void CDF_plateau::ajout(std::pair <Point,bool> A){
  //=== On rajoute le Point dans la List ===
  this->List.push_back(A);
}

void* CDF_plateau::dessus(std::pair <Point,bool> A){
    //=== On rajoute le Point dans la List ===
  if(!this->decalage){
    this->List[0] = A;
  }
  else{
    this->List.push_back(A);
    for(int i = this->List.size() - 1; i > 0; i--){
      std::pair<Point,bool> tmp = this->List[i];
      this->List[i] = this->List[i-1];
      this->List[i-1] = tmp;
    }
  }
}


void CDF_plateau::Lancement(){
  // Le roboot attent le signal..
  this->Trigger();
  this->decalage = false;
  //=== Tant que ma List des point n'est pas vide ===
  while(!this->List.empty()){
    //=== je ouvre ou ferme ma pince ===
    if((*(this->List.begin())).second){
      if(!this->pince.SomeThingTaken())
        this->pince.autoGrab();
      else
        this->pince.relax();
    }
    //=== j'avance a mon premier point de ma List ===
    this->direction((*(this->List.begin())).first);
    //=== je calcule la distance qui me reste a faire ===
    this->distance = sqrt(pow((*this->List.begin()).first.x - this->A.x,2) + pow((*this->List.begin()).first.y - this->A.y,2));
    //=== j'avance jusqu'a être a la distance shoutaie ===
    while(this->asservisement.avancement(true) <= this->distance){
      //=== je regarde mes capteur ===
      this->Dectection();
    }
    //=== je reset ma valeur de decalge ( à voir dans le Contournement) ===
    this->decalage = false;
    //=== Assignation de les point x et y
    this->A.x = (*this->List.begin()).first.x;
    this->A.y = (*this->List.begin()).first.y;
    //=== j'écrase mon premier point de la Liste ===
    this->List.erase(this->List.begin());
    //=== je reset mes valeur d'asservisement ===
    this->asservisement.stop();
  }
}

void CDF_plateau::Contournement(int sens){
  //=== je suis dans un parcour d'évitement ===
  this->decalage = true;
  //=== Assignation de les point x et y ===
  this->A.x += this->asservisement.avancement(true) * cos(this->angle);
  this->A.y += this->asservisement.avancement(true) * sin(this->angle);
  //=== je reset mes valeur d'asservisement ===
  this->asservisement.stop();
  if(sens){
    if(this->decalage)
      this->dessus(std::pair<Point,bool> (Point{this->A.x,this->A.y + 0.5},false));
    else
      this->dessus(std::pair<Point,bool> (Point{this->A.x,this->A.y - 0.5},false));
  }else{
    if(this->decalage)
      this->dessus(std::pair<Point,bool> (Point{this->A.x,this->A.y - 0.5},false));
    else
      this->dessus(std::pair<Point,bool> (Point{this->A.x,this->A.y + 0.5},false));
  }
  //=== j'avance a mon premier point de ma List ===
  this->direction((*(this->List.begin())).first);
  //=== je calcule la distance qui me reste a faire ===
  this->distance = sqrt(pow((*this->List.begin()).first.x - this->A.x,2) + pow((*this->List.begin()).first.y - this->A.y,2));
}

void CDF_plateau::direction(Point &B){
  //=== je reset mes valeur d'asservisement ===
  this->asservisement.stop();
  //=== je calcule l'angle a effectuer ===
  double angle;
  angle = atan2(B.x - this->A.x ,B.y - this->A.y)*180/PI - this->angle;
  if(angle > 180)
    angle = -angle+180;
  if(angle < -180)
    angle = -angle-180;
  //=== Mon roboot tourne sur lui même ===
  this->asservisement.rotation(angle);
  //=== je calcule l'angle ou regarde mon roboot, et je retient ===
  this->angle = atan2(B.x - this->A.x ,B.y - this->A.y)*180/PI;
  //=== je reset mes valeur d'asservisement ===
  this->asservisement.stop();
}

void CDF_plateau::Dectection(){
  //=== je test mon capteur de devant a 35cm ===
  if(capteurAvant.TestCapteur(375.0)){
      this->asservisement.stop();
      //=== je test mon capteur Droite à 20cm ===
      if(!capteurDroite.TestCapteur(200.0))
        this->Contournement(0);
      //=== Si non je test mon capteur Gauche à 20cm ===
      else if(!capteurGauche.TestCapteur(200.0))
        this->Contournement(1);
      else
      //=== j'attend 1 second si mes capteur sont tous pris ===
        delay(1000);
  }
  if(capteurDroite.TestCapteur(200.0) && capteurGauche.TestCapteur(200.0))
      delay(1000);
}

void CDF_plateau::Trigger(){
  //=== je test si mon capteur Trigger est active
  while(!digitalRead(this->pinTrigger)){
    Serial.print("Trigger : ");
    Serial.println(digitalRead(this->pinTrigger));
    delay(200);
  }
}
