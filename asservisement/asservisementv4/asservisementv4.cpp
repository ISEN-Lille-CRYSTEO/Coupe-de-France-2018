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
  this->diff = calculDistance(this->tick_codeuse_R) -  calculDistance(this->tick_codeuse_L);
  Serial.println(this->diff);
	digitalWrite(this->MAvantMD,sens);
	digitalWrite(this->MAvantMG,sens);
  digitalWrite(this->MArriereMD,!sens);
  digitalWrite(this->MArriereMG,!sens);
  if(abs(this->diff) > 0.1)
    this->arret();

 	if(this->diff < -0.01){//la roue codeuse a gauche va tro vitee
 		this->valL += 1;
   	if(this->valL > Max)
    	this->valL = Max;
 	}
 	else if(this->diff > 0.01){//la roue codeuse a droite va tro vitee
   		this->valR += 1;
   	if(this->valR > Max)
     	this->valR = Max;
 	}
 	else {//Si non vitesse constance
   		this->valL = Min;
   		this->valR = Min;
 	}
 	analogWrite(this->PDroit,this->valR);
 	analogWrite(this->PGauche,this->valL);

  if(this->diff >= 0)
    return calculDistance(this->tick_codeuse_R);
  else
    return calculDistance(this->tick_codeuse_L);
}

double CDF_asservisement::rotation(double degree){
  if(degre >= 0)
    this.valeur = true;
  else
    this.valeur = false;
  this->arret();
  delay(10);
 	this->valL = 215;// On diminue la vitesse des roue.
 	this->valR = 215;
 	analogWrite(this->PDroit,this->valR);
 	analogWrite(this->PGauche,this->valL);

	digitalWrite(this->MAvantMG,!valeur);
 	digitalWrite(this->MAvantMD,valeur);
 	delay(10); // on inverse un des 2 motor.
 	digitalWrite(this->MArriereMG,valeur);
 	digitalWrite(this->MArriereMD,!valeur);

  this->tick_codeuse_R = 0;
 	this->tick_codeuse_L = 0;
 	while(calculDistance(this->tick_codeuse_R) < Tour*abs(degree/360) && calculDistance(this->tick_codeuse_L) < Tour*abs(degree/360)){
 		Serial.print(Tour*(degree/360));
 	}
  this->arret();

 	digitalWrite(this->MArriereMG,LOW);
 	digitalWrite(this->MArriereMD,LOW);
 	delay(10);// on remet les 2 motor en marche avant.
  this->valL = Min;
  this->valR = Min;
}

double CDF_asservisement::calculDistance(int tick_codeuse){
 	double nombre_tours = abs((double) tick_codeuse) / (double) nombreTicksPour1TourDeRoue;
 	double metre_parcourue = (double) nombre_tours * (double) perimetreRoueCodeuse; // en mêtres
 	return (double) metre_parcourue;
}

void CDF_asservisement::arret(){
  digitalWrite(this->MArriereMG,LOW);
 	digitalWrite(this->MArriereMD,LOW);
  digitalWrite(this->MAvantMG,LOW);
 	digitalWrite(this->MAvantMG,LOW);
  analogWrite(this->PDroit,225);
  analogWrite(this->PGauche,225);
  this->sens = 0;
  this->tick = this->tick_codeuse_L > this->tick_codeuse_R ? this->tick_codeuse_R : this->tick_codeuse_L ;
  delay(10);
  while(this->tick_codeuse_L > this->tick || this->tick_codeuse_R > this->tick){
    if(this->tick_codeuse_L > 0)
 	    digitalWrite(this->MArriereMG,HIGH);
    else{
      digitalWrite(this->MArriereMG,LOW);
      analogWrite(this->PGauche,255);
    }
    if(this->tick_codeuse_R > 0)
      digitalWrite(this->MArriereMD,HIGH);
    else{
      analogWrite(this->PDroit,255);
      digitalWrite(this->MArriereMD,LOW);
    }
  }
  delay(10);
  digitalWrite(this->MArriereMG,LOW);
  digitalWrite(this->MArriereMD,LOW);
  this->sens = 1;
  this->tick_codeuse_R = 0;
  this->tick_codeuse_L = 0;
}

void CDF_asservisement::stop(){
  analogWrite(this->PDroit,255);
  analogWrite(this->PGauche,255);
}
