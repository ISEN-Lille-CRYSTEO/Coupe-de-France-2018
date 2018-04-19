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

void CDF_plateau::attrape(){
  while(this->asservisement.avancement(true)){
    //=== a gére, bouger légerement a gauche et a droite;
  if(capteurAvant.TestCapteur(150.0)){
    this->asservisement.arret();
    this->pince.autoGrab();
    if(this->pince.SomeThingTaken())
      break;
    }
  }
}
struct bite{
  int A;
  int G;
  int D;
  bite(int A,int G,int D){
    this->A = A;
    this->G = G;
    this->D = D;
  };
  bool operator==(bite  const &b){
    if(this->A == b.A && this->G == b.G && this->D == b.D)
      return true;
    return false;
  };
};

void CDF_plateau::direction(){
  bite A = bite(capteurAvant.TestCapteur(300.0),capteurGauche.TestCapteur(300.0),capteurDroite.TestCapteur(300.0));
    if(A == bite(0,0,0))
      this->angle = 0;
    else if(A == bite(0,0,1)){
      this->angle = 0;
      this->cote = 1;
    }
    else if(A == bite(0,1,0))
      this->angle = 180;
    else if(A == bite(0,1,1))
      this->angle = 45;
    else if(A == bite(1,0,0))
      this->angle = 180;
    else if(A == bite(1,0,1))
      this->angle = 90;
    else if(A == bite(1,1,0)){
      this->angle = 0;
      this->cote = 1;
    }
    else if(A == bite(1,1,1))
      this->angle = 135;
  if(this->cote){
    for(auto i : this->List)
      i.first.x = - i.first.x;
  }
}

void CDF_plateau::Lancement(){
  // Le roboot attent le signal..
  this->Trigger();
  // le roboot se dirige
  this->direction();
  this->decalage = false;
  //=== Tant que ma List des point n'est pas vide ===
  while(!this->List.empty()){
    //=== j'avance a mon premier point de ma List ===
    this->direction((*(this->List.begin())).first);
    //=== je calcule la distance qui me reste a faire ===
    this->distance = sqrt(pow((*this->List.begin()).first.x - this->A.x,2) + pow((*this->List.begin()).first.y - this->A.y,2));
    //=== j'avance jusqu'a être a la distance shoutaie ===
    Serial.println(this->distance);
    if((*(this->List.begin())).second){
      this->distance -= 0.1;
    }
    Serial.println(this->distance);
    while(this->asservisement.avancement(true) <= this->distance){
      //=== je regarde mes capteur ===
      Serial.println(this->asservisement.avancement(true));
      this->Dectection();
    }
    //=== je ouvre ou ferme ma pince ===
    if((*(this->List.begin())).second){
      if(this->attrap){
        this->attrape();
        this->attrap = false;
      }
      else{
        this->asservisement.arret();
        while(this->asservisement.avancement(true) <= 0.4){;}
        this->pince.relax();
        this->attrap = true;
        this->asservisement.arret();
        while(this->asservisement.avancement(false) <= 0.2){;}
        delay(500);
      }
    }
    //=== je reset ma valeur de decalge ( à voir dans le Contournement) ===
    this->decalage = false;
    //=== Assignation de les point x et y
    this->A.x = (*this->List.begin()).first.x;
    this->A.y = (*this->List.begin()).first.y;
    //=== j'écrase mon premier point de la Liste ===
    this->List.erase(this->List.begin());
    //=== je reset mes valeur d'asservisement ===
    this->asservisement.arret();
  }
    this->asservisement.arret();
}

void CDF_plateau::Contournement(int sens){
  //=== je suis dans un parcour d'évitement ===
  this->decalage = true;
  //=== Assignation de les point x et y ===
  this->A.x += this->asservisement.avancement(true) * cos(this->angle);
  this->A.y += this->asservisement.avancement(true) * sin(this->angle);
  //=== je reset mes valeur d'asservisement ===
  this->asservisement.arret();
  if(sens){
    this->dessus(std::pair<Point,bool> (Point{this->A.x + 0.5,this->A.y},false));
  }else{
      this->dessus(std::pair<Point,bool> (Point{this->A.x - 0.5,this->A.y},false));
  }
  //=== j'avance a mon premier point de ma List ===
  this->direction((*(this->List.begin())).first);
  //=== je calcule la distance qui me reste a faire ===
  this->distance = sqrt(pow((*this->List.begin()).first.x - this->A.x,2) + pow((*this->List.begin()).first.y - this->A.y,2));
  if((*(this->List.begin())).second){
    this->distance -= 0.1;
  }
}

void CDF_plateau::direction(Point &B){
  //=== je reset mes valeur d'asservisement ===
  this->asservisement.arret();
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
  this->asservisement.arret();
}

void CDF_plateau::Dectection(){
  //=== je test mon capteur de devant a 35cm ===
  if(capteurAvant.TestCapteur(300.0)){
      this->asservisement.arret();
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
}

void CDF_plateau::Trigger(){
  //=== je test si mon capteur Trigger est active
  while(!digitalRead(this->pinTrigger)){
    Serial.print("Trigger : ");
    Serial.println(digitalRead(this->pinTrigger));
    delay(200);
  }
}
