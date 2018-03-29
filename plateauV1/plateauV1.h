#ifndef CDF_PLATEAU
#define CDF_PLATEAU

#include <math.h>
#include <Arduino.h>

#include "asservisementv4.h"
#include "capteur.h"

//=== CONSTANTES ===
#define X_plateau_abs 2 // valeur max en x du terrain
#define Y_plateau_abs 2 // valeur max en y du terrain

class CDF_plateau
{
  int pinTrigger; // pin du Trigger.
  double x = 0; // position en abscisse
  double y = 0; // position en ordonée
  double distance = 0;//distance entre les 2 point
  double angle = 90; // angle du roboot
  double decalage = 0; // variable qui compte les test d'évitation
  CDF_capteur capteurDroite;
  CDF_capteur capteurGauche;
  CDF_capteur capteurAvant;
  //CDF_capteur capteurArriere;

public:
  CDF_asservisement asservisement;
  CDF_plateau(int pinTrigger);// constructeur du plateau.
  void parcours(double x,double y); // fait avancer le roboot au point...
  void Trigger();// fonction du Bouton de démarage a fils.
  void Dectection(int distance);// fonction des capteur du roboot
  void Contournement(int sens);// fonction qui fait bouger le roboot sur des point a fin d'éviter les obstacle
  void angle(int x,int y);// fonction qui fait tourner le roboot vers la destination
};

#endif  //CDF_PLATEAU
