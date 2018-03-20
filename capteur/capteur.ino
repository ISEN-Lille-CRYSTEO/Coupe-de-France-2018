#include "capteur.h"

// === Variable ===
CDF_capteur capteurDroite(33,35);
CDF_capteur capteurArriere(37,39);
CDF_capteur capteurGauche(41,43);
CDF_capteur capteurAvant(45,47);

void setup() {
	Serial.begin(115200);   // Initialisation port COM
	Serial.println("Début");
}

void loop() {
	Serial.print("capteur Droite :");
  Serial.println(capteurDroite.TestCapteur());
	Serial.print("capteur Gauche :");
  Serial.println(capteurGauche.TestCapteur());
	/*Serial.print("capteur Arriere :");
	Serial.println(capteurArriere.TestCapteur());
	Serial.print("capteur Avant :");
  Serial.println(capteurAvant.TestCapteur());*/
	delay(2500);
}
