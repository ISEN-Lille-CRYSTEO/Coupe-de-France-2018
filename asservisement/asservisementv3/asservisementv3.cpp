#include "asservisementv3.h"

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
  	this->tick_codeuse_R++;
}

void CDF_asservisement::compteur_tick_L(){
 	this->tick_codeuse_L++;
}

void CDF_asservisement::compteur_tick_moinR(){
  	this->tick_codeuse_R--;
}

void CDF_asservisement::compteur_tick_moinL(){
 	this->tick_codeuse_L--;
}

double CDF_asservisement::avancement(int sens){
  this->diff = calculDistance(this->tick_codeuse_R) -  calculDistance(this->tick_codeuse_L);
  Serial.print(this->tick_codeuse_R);
  Serial.print(" et ");
  Serial.print(this->tick_codeuse_L);
  Serial.print(" donc diff => ");
  Serial.println(this->diff);
  Serial.print(" puissance R ");
  Serial.print(valR);
  Serial.print(" puissance L ");
  Serial.println(valL);
	digitalWrite(this->MAvantMD,sens);
	digitalWrite(this->MAvantMG,sens);
  digitalWrite(this->MArriereMD,!sens);
  digitalWrite(this->MArriereMG,!sens);

  if(abs(this->diff) >= Tour/2)//Si pour une raison, il fait un demi tour sur lui même.
    this->arret();

 	if(this->diff > 0){//la roue codeuse a gauche va tro vitee
 		this->valL += 1;
   	if(this->valL > Max)
    	this->valL = Max;
 	}
 	else if(this->diff < 0){//la roue codeuse a droite va tro vitee
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

void CDF_asservisement::rotation(bool valeur,double degree){
 	this->valL = 225;// On diminue la vitesse des roue.
 	this->valR = 225;

 	analogWrite(this->PDroit,this->valR);
 	analogWrite(this->PGauche,this->valL);

	digitalWrite(this->MAvantMG,!valeur);
 	digitalWrite(this->MAvantMD,valeur);
 	delay(50); // on inverse un des 2 motor.
 	digitalWrite(this->MArriereMG,valeur);
 	digitalWrite(this->MArriereMD,!valeur);

  this->tick_codeuse_R = 0;
 	this->tick_codeuse_L = 0;
 	while( abs(calculDistance(this->tick_codeuse_R)) <= Tour*(degree/360) && abs(calculDistance(this->tick_codeuse_L)) <= Tour*(degree/360)){
 		Serial.print(Tour*(degree/360));
 		Serial.print(" <= ");
		Serial.println(calculDistance(this->tick_codeuse_R));
 	}

 	digitalWrite(this->MArriereMG,LOW);
 	digitalWrite(this->MArriereMD,LOW);
 	delay(50);// on remet les 2 motor en marche avant.
 	digitalWrite(this->MAvantMG,HIGH);
 	digitalWrite(this->MAvantMG,HIGH);

 	this->tick_codeuse_R = 0;
 	this->tick_codeuse_L = 0;
}

double CDF_asservisement::calculDistance(unsigned int tick_codeuse){
 	double nombre_tours = (double) tick_codeuse / (double) nombreTicksPour1TourDeRoue;
 	double metre_parcourue = (double) nombre_tours * (double) perimetreRoueCodeuse; // en mêtres
 	return (double) metre_parcourue;
}

void CDF_asservisement::arret(){
  this->tick_codeuse_R = 0;
  this->tick_codeuse_L = 0;
  digitalWrite(this->MArriereMG,LOW);
 	digitalWrite(this->MArriereMD,LOW);
  digitalWrite(this->MAvantMG,LOW);
 	digitalWrite(this->MAvantMG,LOW);
  analogWrite(this->PDroit,235);
  analogWrite(this->PGauche,235);
  while(this->tick_codeuse_L >= 0){
 	  digitalWrite(this->MArriereMG,HIGH);
  }
    digitalWrite(this->MArriereMG,LOW);
  while(this->tick_codeuse_R >= 0){
    digitalWrite(this->MArriereMD,HIGH);
  }
    digitalWrite(this->MArriereMD,LOW);
}
