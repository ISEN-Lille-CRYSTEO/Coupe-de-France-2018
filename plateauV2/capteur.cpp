#include "capteur.h"

CDF_capteur::CDF_capteur(){
	//constructeur par défaut
}

CDF_capteur::CDF_capteur(int pinTrigger,int pinEcho){
  this->pinTrigger = pinTrigger;
  this->pinEcho = pinEcho;
  /* Initialise les broches */
  pinMode(this->pinTrigger, OUTPUT);
  digitalWrite(this->pinTrigger, LOW); // La broche TRIGGER doit être à LOW au repos
  pinMode(this->pinEcho, INPUT);
}

bool CDF_capteur::TestCapteur(float distance){

  /* 1. Lance une mesure de distance en envoyant une impulsion HIGH de 10µs sur la broche TRIGGER */
  digitalWrite(this->pinTrigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(this->pinTrigger, LOW);

  /* 2. Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) */
  long measure = pulseIn(this->pinEcho, HIGH, MEASURE_TIMEOUT);

  /* 3. Calcul la distance à partir du temps mesuré */
  float distance_mm = measure / 2.0 * SOUND_SPEED;
  /*  Serial.print(F("Distance: "));
    Serial.print(distance_mm);
    Serial.print(F("mm ("));
    Serial.print(distance_mm / 10.0, 2);
    Serial.print(F("cm, "));
    Serial.print(distance_mm / 1000.0, 2);
    Serial.println(F("m)"));*/
  if(distance_mm != 0)
    if(distance_mm < distance)
      return true;
  return false;
  /* Délai d'attente pour éviter d'afficher trop de résultats à la seconde */
}
