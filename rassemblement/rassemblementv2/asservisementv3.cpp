#include "asservisementv3.h"

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
  this->MoteurArriere(LOW);
  this->MoteurAvant(LOW);
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
  this->MoteurAvant(this->sens);
  this->MoteurArriere(!this->sens);
  this->redirection();
 	analogWrite(this->PDroit,this->valR);
 	analogWrite(this->PGauche,this->valL);
  if(this->diff >= 0)
    return calculDistance(this->tick_codeuse_R);
  else
    return calculDistance(this->tick_codeuse_L);
}

double CDF_asservisement::rotation(bool valeur,double degree){
  this->stop();
 	this->valL = 215;// On diminue la vitesse des roue.
 	this->valR = 215;

	digitalWrite(this->MAvantMG,!valeur);
 	digitalWrite(this->MAvantMD,valeur);
 	delay(10); // on inverse un des 2 motor.
 	digitalWrite(this->MArriereMG,valeur);
 	digitalWrite(this->MArriereMD,!valeur);

  analogWrite(this->PDroit,this->valR);
 	analogWrite(this->PGauche,this->valL);

  this->tick_codeuse_R = 0;
 	this->tick_codeuse_L = 0;
 	while(calculDistance(this->tick_codeuse_R) < Tour*(degree/360) && calculDistance(this->tick_codeuse_L) < Tour*(degree/360)){
 		Serial.print(Tour*(degree/360));
 	}
  this->stop();
}

double CDF_asservisement::calculDistance(int tick_codeuse){
 	double nombre_tours = abs((double) tick_codeuse) / (double) nombreTicksPour1TourDeRoue;
 	double metre_parcourue = (double) nombre_tours * (double) perimetreRoueCodeuse; // en mêtres
 	return (double) metre_parcourue;
}

void CDF_asservisement::redirection(){
  this->diff = (abs(this->tick_codeuse_R) - abs(this->tick_codeuse_L));
  if((this->diff) < -200){//la roue codeuse a gauche va tro vitee
    this->valL += abs(log(abs(this->diff)/1250));
    if(this->valL > Max)
      this->valL = Max;
  }
  else if((this->diff) > 200){//la roue codeuse a droite va tro vitee
      this->valR += abs(log(abs(this->diff)/1250));
    if(this->valR > Max)
      this->valR = Max;
  }
  else {//Si non vitesse constance
      this->valL = Min;
      this->valR = Min;
  }
}

void CDF_asservisement::stop(){
  delay(250);
  this->MoteurArriere(LOW);
  this->MoteurAvant(LOW);
  this->tick_codeuse_R = 0;
  this->tick_codeuse_L = 0;
  this->Degretion();
  this->sens = 1;
  this->diff = 0;
  this->valL = Min;
  this->valR = Min;
  delay(250);
}

void CDF_asservisement::MoteurAvant(bool sens){
  digitalWrite(this->MAvantMG,sens);
  digitalWrite(this->MAvantMD,sens);
}

void CDF_asservisement::MoteurArriere(bool sens){
  digitalWrite(this->MArriereMD,sens);
  digitalWrite(this->MArriereMG,sens);
}

void CDF_asservisement::Degretion(){
  while(this->valR < 255 || this->valL < 255){
    this->redirection();
    this->valL += 1;
    this->valR += 1;
    if(this->valL > Max)
      this->valL = Max;
    if(this->valR > Max)
      this->valR = Max;
    analogWrite(this->PDroit,this->valL);
    analogWrite(this->PGauche,this->valR);
    delay(10);
  }
}
