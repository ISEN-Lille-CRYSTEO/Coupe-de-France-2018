#ifndef CDF_PLATEAU
#define CDF_PLATEAU

#include "asservisementv4.h"
#include <math.h>

//=== CONSTANTES ===
#define X_plateau_abs 2 // valeur max en x du terrain
#define Y_plateau_abs 2 // valeur max en y du terrain

class CDF_plateau
{
  double x = 0; // position en abscisse
  double y = 0; // position en ordonée
  double distance = 0;//distance entre les 2 point
  double angle = 0; // angle du roboot

public:
  CDF_asservisement asservisement;
  CDF_plateau();
  void parcours(double x,double y); // fait avancer le roboot au point...
};

#endif  //CDF_PLATEAU
