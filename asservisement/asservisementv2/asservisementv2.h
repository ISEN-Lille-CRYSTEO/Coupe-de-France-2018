#ifndef CDF_ASSERVISEMENT
#define CDF_ASSERVISEMENT

#include <Arduino.h>

//=== CONSTANTES ===
#define Max 255 // vitesse null, 0 %
#define Min 200 // vitesse de croissière, 25 %
#define diametreRoueCodeuse 0.05228 // 52,28mm
#define diametreRoueMotor 0.285 //285mm
#define nombreTicksPour1TourDeRoue 1250
#define Pi 3.14159
#define perimetreRoueCodeuse diametreRoueCodeuse*Pi
#define demitour (Pi*diametreRoueMotor)/2 // divisé par deux pour un quart de tour

class CDF_ASSERVISEMENT
{
  //=== VARIABLE ===
  unsigned int tick_codeuse_R = 0;   // Compteur de tick de la codeuse
  unsigned int tick_codeuse_L = 0;   // Compteur de tick de la codeuse
  unsigned int valL = Min;
  unsigned int valR = Min + 2; // augement la linéarité du roboot
  double compte = 0; // nombre de mêtres parcourue
  int diff = 0; // difference des codeuse
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
  CDF_ASSERVISEMENT(int pinEGAvant,int pinEGArriere,int pinEDAvant,int pinEDArriere,int PDroit,int PGauche,int MAavantMG,int MArrierMG,int MAavantMD,int MArrierMD);
  // augement le nombre de tick de la valeur droite
  void compteur_tick_L();
  // augement le nombre de tick de la valeur gauche
  void compteur_tick_R();
  // verifie si le reboot avance droit, et le fait avancer
  void avancement();
  // fait une rotation en fonction des valeur passé en parametre
  void rotation(bool valeur,int distance);
  // cacule la distance parcourue par les roue
  double calculVitesse(unsigned int tick_codeuse);
};






#endif