#include "plateauV1.h"

CDF_plateau::CDF_plateau(){
	//constructeur par défaut
}

void CDF_plateau::parcours(double x,double y){
  this->distance = sqrt(pow(x-this->x,2) + pow(y-this->y,2));
  double angle = atan2(x-this->x,y-this->y)*180/PI - this->angle;
  if(angle > 180)
    angle = -angle+180;
  if(angle < -180)
    angle = -angle-180;
  this->angle = atan2(x-this->x,y-this->y)*180/PI;
  Serial.println(angle);
  this->asservisement.rotation(angle);
  delay(50);
  this->asservisement.stop();
  while(this->asservisement.avancement(true) <= distance){;}
  this->asservisement.stop();
  delay(50);
  this->x = x;
  this->y = y;
}
