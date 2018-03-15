#include "capteur.h"

//=== CONSTANTES ===
#define pinTriggerAvant 2
#define pinEchoAvant 3
// === Variable ===
CDF_capteur capteurAvant(pinTriggerAvant,pinEchoAvant);

void setup() {
	Serial.begin(115200);   // Initialisation port COM
	Serial.println("Début");
	Serial.println(capteurAvant.TestCapteur());
}

void loop() {
}
