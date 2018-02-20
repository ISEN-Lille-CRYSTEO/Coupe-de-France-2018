#include "asservisementv2.h"
#include "pince.h"

int val=10;    // variable to read the value from the analog pin
int valRotor = 90;
int rotorAngle = 0;
bool boutonTrigger = false;
CDF_pince pince(8,9,33);
//=== CONSTANTES ===
#define encodeuseGaucheAvant 13 //encodeur gauche A
#define encodeuseDroiteAvant 11 //encodeur droit A
// === Variable ===
int valeur = 0;
double distanceafaire = 1; // 1 metre
double degre = 180; // 180 degree soit un demi-tour
int distance = 0; // compteur de metre qu'il fait
int sens = 1; // 1 = marche Avant , 0 = Marche arriere
int direction = 1; // 0 = droite, 1 = gauche
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
	pince.rot(90);
   	distance = asservisement.avancement(sens); // fait avancer le reboot tout droit
//=== rotation du roboot === + recul
	if(distance >= distanceafaire){
		asservisement.zero();
		delay(500);
		if(valeur == 0){
			pince.autoGrab();
			valeur = 1;
		}
		else{
      pince.relax();
			valeur = 0;
			delay(500);
			asservisement.avancement(!sens);
			delay(1000);
			distanceafaire = 0.5;
			Serial.println("distanceafaire");
			Serial.println(distanceafaire);
			distance = asservisement.zero();
				}
  	distance = asservisement.rotation(direction,degre);
	}
}
