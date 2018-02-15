//=== CONNECTEUR ===
#define puissanceDroit 6 // puissance du moteur droit
#define puissanceGauche 3 // puissance du moteur gauche
#define funnyAction 33 // Controlleur de lanceur
#define marcheAvantMoteurGauche 22 // position avancer
#define marcheArriereMoteurGauche 23 // position reculer
#define marcheAvantMoteurDroit 52 // position avancer
#define marcheArriereMoteurDroit 53 // position reculer
#define encodeuseGaucheAvant 13 //encodeur gauche A
#define encodeuseGaucheArriere 12 //encodeur gauche B
#define encodeuseDroiteAvant 11 //encodeur droit A
#define encodeuseDroiteArriere 10 //encodeur droit B
//=== CONSTANTES ===
#define diametreRoueCodeuse 0.05228 // 52,28mm
#define diametreRoueMotor 0.285 //285mm
#define nombreTicksPour1TourDeRoue 1250
#define Pi 3.14159
#define perimetreRoueCodeuse diametreRoueCodeuse*Pi
#define demitour (Pi*diametreRoueMotor)/2
#define distancepafaire 1 // 1 metres
#define direction 0 // 0 = droite, 1 = gauche
//=== VARIABLE ===
unsigned int tick_codeuse_R = 0;   // Compteur de tick de la codeuse
unsigned int tick_codeuse_L = 0;   // Compteur de tick de la codeuse
unsigned int valL = 200;
unsigned int valR = 202;
double compte = 0;
int diff = 0;
int r = 0;

void setup() {
	Serial.begin(115200);   // Initialisation port COM
//=== FunnyAction ===
	pinMode(funnyAction,OUTPUT);
	digitalWrite(funnyAction,LOW);
//=== Moteur ===
	pinMode(puissanceDroit,OUTPUT);
 	pinMode(puissanceGauche,OUTPUT);
 	pinMode(marcheAvantMoteurDroit,OUTPUT);
 	pinMode(marcheArriereMoteurDroit,OUTPUT);
 	pinMode(marcheAvantMoteurGauche,OUTPUT);
 	pinMode(marcheArriereMoteurGauche,OUTPUT);
 	pinMode(encodeuseGaucheAvant,INPUT);
 	pinMode(encodeuseGaucheArriere,INPUT);
 	pinMode(encodeuseDroiteAvant,INPUT);
 	pinMode(encodeuseDroiteArriere,INPUT);
//=== Attachement au fonction ===
 	attachInterrupt(encodeuseGaucheAvant, compteur_tick_L, CHANGE);
 	attachInterrupt(encodeuseDroiteAvant, compteur_tick_R, CHANGE);
//=== Allumage des motor ===
 	digitalWrite(marcheAvantMoteurDroit,LOW);
 	digitalWrite(marcheArriereMoteurDroit,LOW);
 	digitalWrite(marcheAvantMoteurGauche,LOW);
 	digitalWrite(marcheArriereMoteurGauche,LOW);
 	analogWrite(puissanceDroit,valR);
 	analogWrite(puissanceGauche,valL);
//=== FunnyAction by ....
 	delay(5000);
 	digitalWrite(funnyAction,HIGH);
 	tick_codeuse_R = 0;
 	tick_codeuse_L = 0;
}

void loop() {   
//=== Démarrage des moteur === 
	digitalWrite(marcheAvantMoteurDroit,HIGH);
	digitalWrite(marcheAvantMoteurGauche,HIGH); 
 	if(calculVitesse(tick_codeuse_R) > calculVitesse(tick_codeuse_L))
 		compte = calculVitesse(tick_codeuse_R);
 	else
 		compte = calculVitesse(tick_codeuse_L);

//=== rotation du roboot ===
   	compte = rotation(direction,compte,distancepafaire);

//=== Avancement du roboot === 
   	avancement(calculVitesse(tick_codeuse_R) -  calculVitesse(tick_codeuse_L)); // fait avancer le reboot tout droit
}

void compteur_tick_R(){
  tick_codeuse_R++;
}
void compteur_tick_L(){
 	tick_codeuse_L++;
}

//Si il tourne a gauche, gauche va tro vite
void avancement(int diff){
 	if(diff > 0){//la roue codeuse a gauche va tro vitee
 		valL += 1;
   	if(valL > 255)
    	valL = 255;
 	}
 	else if(diff < 0){//la roue codeuse a droite va tro vitee
   		valR += 1;
   	if(valR > 255)
     	valR = 255;
 	}
 	else {//Si non vitesse constance
   		valL = 200;
   		valR = 202;
 	}
 	analogWrite(puissanceDroit,valR);
 	analogWrite(puissanceGauche,valL);
 	delay(10);
}

int rotation(bool valeur,int compte,int distance){
	if(compte >= distance){
 		valL = 225;// On diminue la vitesse des roue.
 		valR = 225;
 		analogWrite(puissanceDroit,valR);
 		analogWrite(puissanceGauche,valL);

 		digitalWrite(marcheAvantMoteurGauche,!valeur);
 		digitalWrite(marcheAvantMoteurDroit,valeur);
 		delay(50); // on inverse un des 2 motor.
 		digitalWrite(marcheArriereMoteurGauche,valeur);
 		digitalWrite(marcheArriereMoteurDroit,!valeur); 
 
 		tick_codeuse_L = 0;
 		tick_codeuse_R = 0;
 		while(calculVitesse(tick_codeuse_R) <= demitour && calculVitesse(tick_codeuse_L) <= demitour){
 			Serial.print(demitour);
 			Serial.print(" <= ");
			Serial.println(calculVitesse(tick_codeuse_R));
 		}

 		digitalWrite(marcheArriereMoteurGauche,LOW);
 		digitalWrite(marcheArriereMoteurDroit,LOW); 
 		delay(50);// on remet les 2 motor en marche avant.
 		digitalWrite(marcheAvantMoteurGauche,HIGH);
 		digitalWrite(marcheAvantMoteurDroit,HIGH);

 		tick_codeuse_L = 0;
 		tick_codeuse_R = 0;
 		return 0;

	}else{
		return compte;
	}
}

double calculVitesse(unsigned int tick_codeuse){
 	double nombre_tours = (double) tick_codeuse / (double) nombreTicksPour1TourDeRoue;
 	double metre_parcourue = (double) nombre_tours * (double) perimetreRoueCodeuse; // en mêtres
 	return (double) metre_parcourue;
}
