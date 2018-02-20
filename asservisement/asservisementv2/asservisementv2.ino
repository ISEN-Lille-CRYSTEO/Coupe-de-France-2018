#include "asservisementv2.h"

//=== CONSTANTES ===
#define distancepafaire 1 // 1 metres
#define direction 0 // 0 = droite, 1 = gauche
CDF_ASSERVISEMENT asservisement(13,12,11,10,6,3,22,23,52,53);

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
