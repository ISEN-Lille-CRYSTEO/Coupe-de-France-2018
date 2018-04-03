#ifndef CDF_CAPTEUR
#define CDF_CAPTEUR

#include <math.h>
#include <Arduino.h>

//=== CONSTANTES ===
class CDF_capteur
{
  int pinTrigger;
  int pinEcho;
  unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s
  float SOUND_SPEED = 340.0 / 1000;

public:
  CDF_capteur(); // Constructeur
  CDF_capteur(int pinTrigger,int pinEcho); // fonction qui initialise le capteur
  bool TestCapteur(float distance);// fonction qui ecoute le capteur
};

#endif  //CDF_CAPTEUR
