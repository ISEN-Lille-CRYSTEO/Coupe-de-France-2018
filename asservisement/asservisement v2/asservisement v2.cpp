#include "asservisement v2.h"

//=== Attachement des pin/Encodeuse ===
CDF_asservisement(int pinEGAvant,int pinEGArriere,int pinEDAvant,int pinEDArriere,int PDroit,int PGauche,int MAavantMG,int MArrierMG,int MAavantMD,int MArrierMD){
  this.pinEGAvant = pinEGAvant;
  this.pinEGArriere = pinEGArriere;
  this.pinEDAvant = pinEDAvant;
  this.pinEDArriere = pinEDArriere;
  this.PDroit = PDroit;
  this.PGauche = PGauche;
  this.MAavantMG = MAavantMG;
  this.MArriereMG = MArrierMG;
  this.MAavantMD = MAavantMD;
  this.MArriereMD = MArrierMD;
//=== Attachement au fonction ===
 	attachInterrupt(this.pinEGAvant, this.compteur_tick_L, CHANGE);
 	attachInterrupt(this.pinEDAvant, this.compteur_tick_R, CHANGE);
//=== Encodeuse ===
  pinMode(this.pinEGAvant,INPUT);
 	pinMode(this.pinEGArriere,INPUT);
 	pinMode(this.pinEDAvant,INPUT);
 	pinMode(this.pinEDArriere,INPUT);
//=== Motor ===
  pinMode(this.PDroit,OUTPUT);
  pinMode(this.PGauche,OUTPUT);
  pinMode(this.MAavantMG,OUTPUT);
  pinMode(this.MArriereMG,OUTPUT);
  pinMode(this.MAavantMD,OUTPUT);
  pinMode(this.MArriereMD,OUTPUT);
//=== Allumage des motor ===
 	digitalWrite(this.MAavantMG,LOW);
 	digitalWrite(this.MArriereMG,LOW);
 	digitalWrite(this.MAavantMD,LOW);
 	digitalWrite(this.MArriereMD,LOW);
}

void CDF_ASSERVISEMENT::compteur_tick_R(){
  this.tick_codeuse_R++;
}
void CDF_ASSERVISEMENT::compteur_tick_L(){
 	this.tick_codeuse_L++;
}

//Si il tourne a gauche, gauche va tro vite
void CDF_ASSERVISEMENT::avancement(){
  this.diff = calculVitesse(this.tick_codeuse_R) -  calculVitesse(this.tick_codeuse_L)
  if(this.diff >= 0)
    this.compte = calculVitesse(this.tick_codeuse_R);
  else
    this.compte = calculVitesse(this.tick_codeuse_L);

	digitalWrite(this.MAvantMD,HIGH);
	digitalWrite(this.MAvantMG,HIGH);
 	if(this.diff > 0){//la roue codeuse a gauche va tro vitee
 		this.valL += 1;
   	if(this.valL > Max)
    	this.valL = Max;
 	}
 	else if(this.diff < 0){//la roue codeuse a droite va tro vitee
   		this.valR += 1;
   	if(this.valR > Max)
     	this.valR = Max;
 	}
 	else {//Si non vitesse constance
   		this.valL = Min;
   		this.valR = Min + 2;
 	}
 	analogWrite(this.PDroit,this.valR);
 	analogWrite(this.PGauche,this.valL);
 	delay(10);
}

int CDF_ASSERVISEMENT::rotation(bool valeur,int distance){
	if(this.compte >= distance){
 		this.valL = 225;// On diminue la vitesse des roue.
 		this.valR = 225;
 		analogWrite(this.PDroit,this.valR);
 		analogWrite(this.PGauche,this.valL);

 		digitalWrite(this.MAvantMG,!valeur);
 		digitalWrite(this.MAvantMD,valeur);
 		delay(50); // on inverse un des 2 motor.
 		digitalWrite(this.MArriereMG,valeur);
 		digitalWrite(this.MArriereMD,!valeur);

 		while(calculVitesse(this.tick_codeuse_R) <= demitour && calculVitesse(this.tick_codeuse_L) <= demitour){
 			Serial.print(demitour);
 			Serial.print(" <= ");
			Serial.println(calculVitesse(this.tick_codeuse_R));
 		}

 		digitalWrite(this.MArriereMG,LOW);
 		digitalWrite(this.MArriereMD,LOW);
 		delay(50);// on remet les 2 motor en marche avant.
 		digitalWrite(this.MAvantMG,HIGH);
 		digitalWrite(this.MAvantMG,HIGH);

 		this.tick_codeuse_L = 0;
 		this.tick_codeuse_R = 0;
 		return 0;

	}else{
		return compte;
	}
}

double CDF_ASSERVISEMENT::calculVitesse(unsigned int tick_codeuse){
 	double nombre_tours = (double) tick_codeuse / (double) nombreTicksPour1TourDeRoue;
 	double metre_parcourue = (double) nombre_tours * (double) perimetreRoueCodeuse; // en mêtres
 	return (double) metre_parcourue;
}
