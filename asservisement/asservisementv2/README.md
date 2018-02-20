=== Roue codeuse ===
#define encodeuseGaucheAvant 13 //encodeur gauche A
#define encodeuseGaucheArriere 12 //encodeur gauche B
#define encodeuseDroiteAvant 11 //encodeur droit A
#define encodeuseDroiteArriere 10 //encodeur droit B

//=== CONNECTEUR ===
#define puissanceDroit 6 // puissance du moteur droit
#define puissanceGauche 3 // puissance du moteur gauche
#define marcheAvantMoteurGauche 22 // position avancer
#define marcheArriereMoteurGauche 23 // position reculer
#define marcheAvantMoteurDroit 52 // position avancer
#define marcheArriereMoteurDroit 53 // position reculer

//=== CONSTANTES ===
#define Max 255 // vitesse null, 0 %
#define Min 200 // vitesse de croissière, 25 %
#define diametreRoueCodeuse 0.05228 // 52,28mm
#define diametreRoueMotor 0.285 //285mm
#define nombreTicksPour1TourDeRoue 1250
#define Pi 3.14159
#define perimetreRoueCodeuse diametreRoueCodeuse*Pi
#define demitour (Pi*diametreRoueMotor)/2 // divisé par deux pour un quart de tour
