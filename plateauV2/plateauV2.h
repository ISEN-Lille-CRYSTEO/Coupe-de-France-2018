#ifndef CDF_PLATEAU
#define CDF_PLATEAU

#include <math.h>
#include <Arduino.h>
#include <vector>

#include "asservisementV4/asservisementv4.h"
#include "capteur/capteur.h"

struct Point
{
    double x;
    double y;
};

class CDF_plateau
{
  std::vector<Point> List;   // List des point a parcourir
  int pinTrigger;       // pin du Trigger.
  Point A;              // Point ou le roboot se situe
  double distance = 0;  // distance entre les 2 point
  double angle = 90;    // angle du roboot
  bool decalage = false;  // variable qui compte les test d'évitation
  CDF_capteur capteurDroite;
  CDF_capteur capteurGauche;
  CDF_capteur capteurAvant;

public:
  CDF_asservisement asservisement;
  CDF_plateau(int pinTrigger);             // constructeur du plateau.
  void* dessus(const Point A);                    // ajoute un point au début de la list
  void ajout(Point A);                     // rajoute le point a la liste
  void Lancement();                        // démare le programme du roboot
  void Trigger();                          // fonction du Bouton de démarage a fils.
  void Dectection();            // fonction des capteur du roboot
  void Contournement(int sens);// fonction qui fait bouger le roboot sur des point a fin d'éviter les obstacle
  void direction(Point B);             // fonction qui fait tourner le roboot vers la destination
};


#endif  //CDF_PLATEAU
