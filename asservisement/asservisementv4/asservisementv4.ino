#include "asservisementv4.h"

//=== CONSTANTES ===
#define encodeuseGaucheAvant 13 //encodeur gauche A
#define encodeuseDroiteAvant 11 //encodeur droit A
#define encodeuseGaucheArriere 12 //encodeur gauche A
#define encodeuseDroiteArriere 10 //encodeur droit A
// === Variable ===
double distancepafaire = 0.5; // 1 metre
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
 	attachInterrupt(digitalPinToInterrupt(encodeuseGaucheAvant), [&](){asservisement.compteur_tick_L1();}, RISING);
 	attachInterrupt(digitalPinToInterrupt(encodeuseDroiteAvant), [&](){asservisement.compteur_tick_R1();}, RISING);
	attachInterrupt(digitalPinToInterrupt(encodeuseGaucheArriere), [&](){asservisement.compteur_tick_L2();}, RISING);
 	attachInterrupt(digitalPinToInterrupt(encodeuseDroiteArriere), [&](){asservisement.compteur_tick_R2();}, RISING);
}

void loop() {
	Serial.println(asservisement.avancement(sens));
	Serial.println(distancepafaire);
	while(asservisement.avancement(sens) <= distancepafaire){
		delay(1);
	}
  asservisement.rotation(degre);
}
