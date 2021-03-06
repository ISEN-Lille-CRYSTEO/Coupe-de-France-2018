#include "asservisementv4.h"

CDF_asservisement::CDF_asservisement(){
	//constructeur par défaut
}

CDF_asservisement::CDF_asservisement(int pinEGAvant,int pinEGArriere,int pinEDAvant,int pinEDArriere,int PDroit,int PGauche,int MAvantMG,int MArrierMG,int MAvantMD,int MArrierMD){
  this->pinEGAvant = pinEGAvant;
  this->pinEGArriere = pinEGArriere;
  this->pinEDAvant = pinEDAvant;
  this->pinEDArriere = pinEDArriere;
  this->PDroit = PDroit;
  this->PGauche = PGauche;
  this->MAvantMG = MAvantMG;
  this->MArriereMG = MArrierMG;
  this->MAvantMD = MAvantMD;
  this->MArriereMD = MArrierMD;
  //=== Encodeuse ===
  pinMode(this->pinEGAvant,INPUT);
  pinMode(this->pinEGArriere,INPUT);
  pinMode(this->pinEDAvant,INPUT);
  pinMode(this->pinEDArriere,INPUT);
  //=== Motor ===
  pinMode(this->PDroit,OUTPUT);
  pinMode(this->PGauche,OUTPUT);
  pinMode(this->MAvantMG,OUTPUT);
  pinMode(this->MArriereMG,OUTPUT);
  pinMode(this->MAvantMD,OUTPUT);
  pinMode(this->MArriereMD,OUTPUT);
  //=== Allumage des motor ===
  digitalWrite(this->MAvantMG,LOW);
  digitalWrite(this->MArriereMG,LOW);
  digitalWrite(this->MAvantMD,LOW);
  digitalWrite(this->MArriereMD,LOW);
}

void CDF_asservisement::compteur_tick_R(){
  if(this->sens)
  	this->tick_codeuse_R++;
  else
    this->tick_codeuse_R--;
}

void CDF_asservisement::compteur_tick_L(){
  if(this->sens)
 	  this->tick_codeuse_L++;
  else
    this->tick_codeuse_L--;
}

double CDF_asservisement::avancement(int sens){
  this->sens = sens;
	digitalWrite(this->MAvantMD,sens);
	digitalWrite(this->MAvantMG,sens);
  digitalWrite(this->MArriereMD,!sens);
  digitalWrite(this->MArriereMG,!sens);
  delay(1);
  analogWrite(this->PDroit,this->valR);
 	analogWrite(this->PGauche,this->valL);

  this->diff = calculDistance(this->tick_codeuse_R) -  calculDistance(this->tick_codeuse_L);
  this->controle();

  if(this->diff >= 0)
    return calculDistance(this->tick_codeuse_R);
  else
    return calculDistance(this->tick_codeuse_L);
}

double CDF_asservisement::rotation(double degree){
  this->stop();
  if(degree >= 0)
    this->valeur = true;
  else
    this->valeur = false;

	digitalWrite(this->MAvantMG,!valeur);
 	digitalWrite(this->MAvantMD,valeur);
 	delay(10); // on inverse un des 2 motor.
 	digitalWrite(this->MArriereMG,valeur);
 	digitalWrite(this->MArriereMD,!valeur);
 	while(calculDistance(this->tick_codeuse_R) < Tour*abs(degree/360) && calculDistance(this->tick_codeuse_L) < Tour*abs(degree/360)){
    this->diff = pow(-1,valeur+1)*(calculDistance(this->tick_codeuse_R) +  pow(-1,valeur)*calculDistance(this->tick_codeuse_L));
    this->controle();
    this->valL = 200 + 30*(this->tick_codeuse_R/Tour*abs(degree/360)) ;
    this->valR = 200 + 30*(this->tick_codeuse_R/Tour*abs(degree/360)) ;
   	analogWrite(this->PDroit,this->valR);
   	analogWrite(this->PGauche,this->valL);
  }
  this->arret();
  this->valL = MinP;
  this->valR = MinP;
}

double CDF_asservisement::calculDistance(int tick_codeuse){
 	double nombre_tours = abs((double) tick_codeuse) / (double) nombreTicksPour1TourDeRoue;
 	double metre_parcourue = (double) nombre_tours * (double) perimetreRoueCodeuse; // en mêtres
 	return (double) metre_parcourue;
}

void CDF_asservisement::controle(){
  if(this->diff < - (int)((double)(this->valL/MaxP)*(double)(1/100)*(double)(exp(this->valL/MaxP)))){
     this->valL += 1;
     if(this->valL > MaxP)
       this->valL = MaxP;
  }
  else if(this->diff > (int)((double)(this->valR/MaxP)*(double)(1/100)*(double)(exp(this->valR/MaxP)))){
     this->valR += 1;
     if(this->valR > MaxP)
        this->valR = MaxP;
  }
  else {//Si non vitesse constance
    this->valL = MinP;
    this->valR = MinP;
  }
  delay(1);
}

void CDF_asservisement::arret(){
  analogWrite(this->PDroit,MaxP);
  analogWrite(this->PGauche,MaxP);
  digitalWrite(this->MArriereMG,LOW);
 	digitalWrite(this->MArriereMD,LOW);
  digitalWrite(this->MAvantMG,LOW);
 	digitalWrite(this->MAvantMG,LOW);
  delay(100);
  this->tick_codeuse_R = 0;
  this->tick_codeuse_L = 0;
}

void CDF_asservisement::stop(){
  this->valL = MinP;
  this->valR = MinP;
  while(this->valL < 254 || this->valR < 254){
    analogWrite(this->PDroit,this->valL++);
    analogWrite(this->PGauche,this->valR++);
    delay(1);
  }
  delay(100);
  this->tick_codeuse_R = 0;
  this->tick_codeuse_L = 0;
}
