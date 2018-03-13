#include "asservisementv4.h"
#include "math.h"

CDF_plateau::CDF_plateau(){
 	this.asservisement = CDF_asservisement(13,12,11,10,6,3,22,23,52,53);
}

void CDF_plateau::parcours(double x,double y){
  this->distance = sqrt((x-this->x)^2 + (y-this->y)^2);
  this->angle = Acos(distance/x) - this.angle;
  asservisement.rotation(true,angle);
  delay(50);
  asservisement.stop();
  while(asservisement.avancement(sens) <= distance){
    serial.println("cc");
  }
  asservisement.stop();
  delay(50);
  this->x = x;
  this->y = y;
}
