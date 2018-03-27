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
  CDF_capteur();
  CDF_capteur(int pinTrigger,int pinEcho);
  bool TestCapteur(float distance);
};

#endif  //CDF_CAPTEUR
