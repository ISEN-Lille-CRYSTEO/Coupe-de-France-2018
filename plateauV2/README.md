# Bouton
  - pinTrigger 31

# Pins roues

## Pin pince
- pinControllepince 8
- pinControllerotor 9
- pinCapteurbouton 7

## Roue codeuse
- encodeuseGaucheAvant 13
- encodeuseGaucheArriere 12
- encodeuseDroiteAvant 11
- encodeuseDroiteArriere 10

## CONNECTEUR
-  puissanceDroit 6
-  puissanceGauche 3
-  marcheAvantMoteurGauche 22
-  marcheArriereMoteurGauche 23
-  marcheAvantMoteurDroit 52
-  marcheArriereMoteurDroit 53

## CONSTANTES
-  Max 255 // vitesse null, 0 %
-  Min 200 // vitesse de croissière, 25 %
-  diametreRoueCodeuse 0.05228 // 52,28mm
-  diametreRoueMotor 0.285 //285mm
-  nombreTicksPour1TourDeRoue 1250
-  Pi 3.14159
-  perimetreRoueCodeuse diametreRoueCodeuse*Pi
-  demitour (Pi*diametreRoueMotor)/2 // divisé par deux pour un quart de tour
