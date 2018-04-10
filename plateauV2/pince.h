#ifndef CDF_PINCE
#define CDF_PINCE

#include <Arduino.h>
#include <Servo.h>

#define MinPince 8
#define MaxPince 60

class CDF_pince
{
	int degreRotor=95;
	int degrePince=50;
	int pinCapteur;
	Servo pince;
	Servo rotor;
public:
	CDF_pince();
	CDF_pince(int pinPince, int pinRotor, int pinCapteur);
	//true si quelquechose est tenu par la pince
	bool SomeThingTaken() const;
	// ferme la pince avec un degré spécifique
	int grab(int degre);
	//attrape automatiquement un objet
	int autoGrab();
	//ouvre la pince a son angle max
	int relax();
	//fait tourner le rotor (position par défaut 90°)
	int rot(int degre);
	//renvoie l'angle de la pince pour calculer un ordre de grandeur de la taille de l'objet tenu
  	int getPinceAngle();

};










#endif
