#include "plateauV1.h"

//=== CONSTANTES ===
#define encodeuseGaucheAvant 13 //encodeur gauche A
#define encodeuseDroiteAvant 11 //encodeur droit A
// === Variable ===
CDF_plateau plateau;

void setup() {
	Serial.begin(115200);   // Initialisation port COM
 	attachInterrupt(digitalPinToInterrupt(encodeuseGaucheAvant), [&](){plateau.asservisement.compteur_tick_L();}, RISING);
 	attachInterrupt(digitalPinToInterrupt(encodeuseDroiteAvant), [&](){plateau.asservisement.compteur_tick_R();}, RISING);
	plateau.parcours(1,0); // le roboot se rend au point (1,0)
	plateau.parcours(1,1); // le roboot se rend au point (1,1)
	plateau.parcours(0,1); // le roboot se rend au point (0,1)
	plateau.parcours(0,0); // le roboot se rend au point (0,0)
}

void loop() {
}
