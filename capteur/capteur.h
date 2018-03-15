#ifndef CDF_CAPTEUR
#define CDF_CAPTEUR

#include <Arduino.h>
#include <math.h>

//=== CONSTANTES ===
class CDF_capteur
{
  int pinTrigger;
  int pinEcho;
  const unsigned long MEASURE_TIMEOUT = 25000UL; // 25ms = ~8m à 340m/s
  const float SOUND_SPEED = 340.0 / 1000;

public:
  CDF_capteur();
  CDF_capteur(int pinTrigger,int pinEcho);
  bool TestCapteur();
};

#endif  //CDF_CAPTEUR
