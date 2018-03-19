#include "capteur.h"

// === Variable ===
CDF_capteur capteurAvant(24,26);
CDF_capteur capteurArriere(28,26);

void setup() {
	Serial.begin(115200);   // Initialisation port COM
	Serial.println("Début");
}

void loop() {
  Serial.println(capteurAvant.TestCapteur());
  delay(1000);
  Serial.println(capteurArriere.TestCapteur());
	Serial.println(" ");
	delay(2500);
}
