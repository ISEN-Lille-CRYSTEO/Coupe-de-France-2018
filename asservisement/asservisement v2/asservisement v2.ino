#include "asservisement v2.h"

//=== Roue codeuse ===
#define encodeuseGaucheAvant 13 //encodeur gauche A
#define encodeuseGaucheArriere 12 //encodeur gauche B
#define encodeuseDroiteAvant 11 //encodeur droit A
#define encodeuseDroiteArriere 10 //encodeur droit B
//=== CONNECTEUR ===
#define puissanceDroit 6 // puissance du moteur droit
#define puissanceGauche 3 // puissance du moteur gauche
#define marcheAvantMoteurGauche 22 // position avancer
#define marcheArriereMoteurGauche 23 // position reculer
#define marcheAvantMoteurDroit 52 // position avancer
#define marcheArriereMoteurDroit 53 // position reculer
//=== CONSTANTES ===
#define distancepafaire 1 // 1 metres
#define direction 0 // 0 = droite, 1 = gauche
CDF_asservisement asservisement(13,12,11,10,6,3,22,23,52,53);

void setup() {
	Serial.begin(115200);   // Initialisation port COM
	Serial.print("Début");
}

void loop() {
//=== rotation du roboot ===
   	asservisement.rotation(direction,distancepafaire);
//=== Avancement du roboot ===
   	asservisement.avancement(); // fait avancer le reboot tout droit
}
