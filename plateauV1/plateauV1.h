#ifndef CDF_ASSERVISEMENT
#define CDF_ASSERVISEMENT

#include <Arduino.h>
#include <asservisementv4.h>

//=== CONSTANTES ===
#define X_plateau_abs 2 // valeur max en x du terrain
#define Y_plateau_abs 2 // valeur max en y du terrain

class CDF_plateau
{
  double x = 0; // position en abscisse
  double y = 0; // position en ordonée
  double distance = 0;//distance entre les 2 point
  double angle = 0; // angle du roboot
  CDF_asservisement asservisement;

public:
  CDF_plateau();
  void parcours(double x,double y); // fait avancer le roboot au point...
};

#endif  //CDF_ASSERTIVESSEMENT
