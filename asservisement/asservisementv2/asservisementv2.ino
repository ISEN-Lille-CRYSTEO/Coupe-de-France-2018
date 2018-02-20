#include "asservisementv2.h"

//=== CONSTANTES ===
#define encodeuseGaucheAvant 13 //encodeur gauche A
#define encodeuseDroiteAvant 11 //encodeur droit A
// === Variable ===
int distancepafaire = 1; // 1 metre
double degre = 180; // 180 degree soit un demi-tour
int distance = 0; // compteur de metre qu'il fait
int sens = 1; // 1 = marche Avant , 0 = Marche arriere
int direction = 0; // 0 = droite, 1 = gauche
CDF_asservisement asservisement;

void setup() {
	Serial.begin(115200);   // Initialisation port COM
	Serial.print("Début");
	/* === Attachement au fonction === */
 	asservisement = CDF_asservisement(13,12,11,10,6,3,22,23,52,53);
 	attachInterrupt(digitalPinToInterrupt(encodeuseGaucheAvant), [&](){asservisement.compteur_tick_L();}, RISING);
 	attachInterrupt(digitalPinToInterrupt(encodeuseDroiteAvant), [&](){asservisement.compteur_tick_R();}, RISING);
}

void loop() {
//=== Avancement du roboot ===
   distance = asservisement.avancement(sens); // fait avancer le reboot tout droit
//=== rotation du roboot === + recul
	if(distance >= distancepafaire){
		distance = asservisement.zero();
		delay(2000);
  	distance = asservisement.rotation(direction,degre);
	}
}
