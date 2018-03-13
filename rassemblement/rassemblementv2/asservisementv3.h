#ifndef CDF_ASSERVISEMENT
#define CDF_ASSERVISEMENT

#include <Arduino.h>

//=== CONSTANTES ===
#define Max 255 // vitesse null, 0 %
#define Min 200 // vitesse de croissière, 25 %
#define diametreRoueCodeuse 0.05228 // 52,28mm
#define espacementRouesMoteur 0.26 //250mm = 25.0cm
#define nombreTicksPour1TourDeRoue 1250
#define Pi 3.14159
#define perimetreRoueCodeuse diametreRoueCodeuse*Pi
#define Tour Pi*espacementRouesMoteur // perimetre d'un cercle entre les 2 roue du roboot

class CDF_asservisement
{
  //=== VARIABLE ===
  int tick_codeuse_R = 0;   // Compteur de tick de la codeuse
  int tick_codeuse_L = 0;   // Compteur de tick de la codeuse
  unsigned int valL = Min;
  unsigned int valR = Min; // augement la linéarité du roboot
  double diff = 0; // difference des codeuse
  int sens = 1; // sens du roboot
  //=== Pin ===
  int pinEGAvant; // encodeuseGaucheAvant
  int pinEGArriere; // encodeuseGaucheArriere
  int pinEDAvant; // encodeuseDroiteAvant
  int pinEDArriere; // encodeuseDroiteArriere
  int PGauche; // puissanceGauche
  int PDroit; // puissanceDroit
  int MAvantMG; // marcheAvantMoteurGauche
  int MAvantMD; // marcheAvantMoteurDroit
  int MArriereMG; // marcheArriereMoteurGauche
  int MArriereMD; // marcheArriereMoteurDroit

public:
  CDF_asservisement();
  CDF_asservisement(int pinEGAvant,int pinEGArriere,int pinEDAvant,int pinEDArriere,int PDroit,int PGauche,int MAavantMG,int MArrierMG,int MAavantMD,int MArrierMD);
  // augement le nombre de tick de la valeur droite
  void compteur_tick_L();
  // augement le nombre de tick de la valeur gauche
  void compteur_tick_R();
  // verifie si le reboot avance droit, et le fait avancer
  double avancement(int sens);
  // fait une rotation en fonction des valeur passé en parametre
  double rotation(bool valeur,double degree);
  // cacule la distance parcourue par les roue
  double calculDistance(int tick_codeuse);
  // remet a zero les compteur_tick
  void redirection();
  // arrete le reboot
  void stop();
  // démare ou éteint les motor
  void MoteurAvant(bool sens);
  void MoteurArriere(bool sens);
  void Degretion();
};

#endif  //CDF_ASSERTIVESSEMENT
