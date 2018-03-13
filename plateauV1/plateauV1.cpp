#include "plateauV1.h"

CDF_plateau::CDF_plateau(){
 	this->asservisement = CDF_asservisement(13,12,11,10,6,3,22,23,52,53);
}

void CDF_plateau::parcours(double x,double y){
  this->distance = sqrt(pow(x-this->x,2) + pow(y-this->y,2));
  Serial.print("la distance est : ");
  Serial.println(this->distance);
  this->angle = acos(x/distance) - this->angle;
  Serial.print("l'angle est :")
  Serial.println(this->angle);
  this->asservisement.rotation(this->angle);
  delay(500);
  this->asservisement.stop();
  while(this->asservisement.avancement(true) >= distance){
    Serial.println("avancer");
  }
  this->asservisement.stop();
  delay(50);
  this->x = x;
  this->y = y;
}
