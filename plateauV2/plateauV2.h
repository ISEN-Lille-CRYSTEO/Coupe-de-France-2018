#ifndef CDF_PLATEAU
#define CDF_PLATEAU

#include <math.h>
#include <Arduino.h>
#include <vector>
#include <map>

#include "asservisementv4.h"
#include "capteur.h"
#include "pince.h"

struct Point
{
    double x;
    double y;
};

class CDF_plateau
{
  std::vector<std::pair<Point,bool>> List;   // List des point a parcourir
  int pinTrigger;       // pin du Trigger.
  Point A;              // Point ou le roboot se situe
  double distance = 0;  // distance entre les 2 point
  double angle = 0;     // angle du roboot
  int cote = 0;         // 0 = gauche, 1 = droite.
  bool decalage = false;// variable qui compte les test d'évitation
  bool attrap = true;
  CDF_capteur capteurDroite;
  CDF_capteur capteurGauche;
  CDF_capteur capteurAvant;
  CDF_pince pince;

public:
  CDF_asservisement asservisement;
  CDF_plateau(int pinTrigger);             // constructeur du plateau.
  void* dessus(std::pair <Point,bool> A);                    // ajoute un point au début de la list
  void ajout(std::pair <Point,bool> A);                     // rajoute le point a la liste
  void Lancement();                        // démare le programme du roboot
  void Trigger();                          // fonction du Bouton de démarage a fils.
  void Dectection();            // fonction des capteur du roboot
  void Contournement(int sens);// fonction qui fait bouger le roboot sur des point a fin d'éviter les obstacle
  void direction(Point &B);             // fonction qui fait tourner le roboot vers la destination
  void attrape(); // fait avancer le reboot pour attraper l'objet
  void direction(); // tourne le roboot en fonction des capteur
};


#endif  //CDF_PLATEAU
