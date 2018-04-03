int sensorPin = A5; // Déclaration de la broche d'entrée
 
// Sortie série à 9600 bauds
void setup()
{
    Serial.begin(9600);
}
 
// Le programme mesure la valeur de tension continue aux bornes de la LDR, il calcule la résistance du capteur <br />// et envoie le résultat vers la sortie série.
 
void loop()
{      
        // La valeur de la tension est mesurée
    int rawValue = analogRead(sensorPin);
        float voltage = rawValue * (5.0/1023) * 1000;
         
        float resitance = 10000 * ( voltage / ( 5000.0 - voltage) );
         
    // Sortie vers l'interface série
    Serial.print("Tension:");   Serial.print(voltage); Serial.print("mV");
    Serial.print(", Resistance:"); Serial.print(resitance); Serial.println("Ohm");
    Serial.println("---------------------------------------");
 
    delay(500);
}
