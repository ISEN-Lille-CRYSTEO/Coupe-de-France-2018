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
	CDF_pince(int pinPince, int pinRotor, int pinCapteur);
	int grab(int degre);
	int autoGrab();
	int relax();
	int rot(int degre);
  int getPinceAngle();
	
};










#endif
