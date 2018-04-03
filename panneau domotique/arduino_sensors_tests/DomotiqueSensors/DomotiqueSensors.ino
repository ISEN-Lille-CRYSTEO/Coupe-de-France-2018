
#include <Adafruit_Sensor.h>
#include "DHT.h"

#define PHOTOPIN A0 // Photoresistor analog Pin

#define DHTPIN 13 // DHT 11 digital Pin
#define DHTTYPE DHT11   // DHT type

// Resistances de 10kohm en provenance des pins de donnees vers la borne + (5V)

DHT dht(DHTPIN, DHTTYPE); // Creation du DHT

void setup() {
    Serial.begin(9600); // Initialistaion du Serial
    
    dht.begin(); // Initialisation du DHT
}
 
void loop() {      
    delay(2000); // Latence entre chaque mesure
                 // Ne pas descendre en dessous de 1000ms, seuil auquel le dht ne peut plus repondre
    
    int photoRaw = analogRead(PHOTOPIN); // Valeur analogique de la photoresistance KY-018
    
    float photoVoltage = photoRaw * (5000.0/1023);  // 5000.0 est Vin
                                                    // 1023 le nombre maximum auquel l'entree analogique peut monter
    
    float photoResistance = 10000 * ( voltage / ( 5000.0 - voltage) );  // Resistance de la cellule photovoltaique
         
    float lux = pow(resitance,-2.981493854) * pow(10,13.07271865); // Valeur en Lux
                                                                   // On a l'equation Lux = pow(R, a) + pow(10, b)
                                                                   // On peut ainsi retrouver les valeurs de a et b en faisant des mesures
                                                                   // Ex: On a Lux = 400 pour R = 3250 et Lux = 10 pour R = 11200
    
    float humidityDHT = dht.readHumidity(); // Humidite 
    float tempDHT = dht.readTemperature(); // Temperature (Celsius)
    
    // On envoie les donnees dans le Serial
    Serial.print(tempDHT);
    Serial.print("°C");
    Serial.println(",");
    Serial.print(humidityDHT);
    Serial.print("%");
    Serial.print(",");
    Serial.println(lux);
    Serial.print("lx");
}
