#include "asservisementv3.h"

// === Variable ===
double distancepafaire = 1; // 1 metre
double degre = 180; // 180 degree soit un demi-tour
bool sens = 1; // 1 = marche Avant , 0 = Marche arriere
bool direction = 0; // 0 = droite, 1 = gauche
CDF_asservisement asservisement(13,12,11,10,6,3,22,23,52,53);

void setup() {
	attachInterrupt(digitalPinToInterrupt(13), [&](){asservisement.compteur_tick_L();}, RISING);
	attachInterrupt(digitalPinToInterrupt(11), [&](){asservisement.compteur_tick_R();}, RISING);
	attachInterrupt(digitalPinToInterrupt(12), [&](){asservisement.compteur_tick_moinL();}, RISING);
	attachInterrupt(digitalPinToInterrupt(10), [&](){asservisement.compteur_tick_moinR();}, RISING);
	Serial.begin(115200);
	Serial.print("Début");
}

void loop() {
	if(asservisement.avancement(sens) >= distancepafaire){
		asservisement.arret();
		delay(1500);
  	asservisement.rotation(direction,degre);
	}
}
