
#include <xc.h>
#include "pic16f690.h"

#define _XTAL_FREQ 8000000



int main() {
    TRISA = 0b00000000;
    TRISB = 0b00000100;//on met tout les pins en sortie sauf RA2=entrée
    
    PORTB = 0b00000000 ;
    PORTA = 0b00000000 ;
    
    for(;;) {
        if (RB6) {//on utilise RA2 comme entrée
            RB4 = 1;
            __delay_us(400);//met le bit RB4 à l'état haut 
            RB4 = 0;
            __delay_us(19600);//remet le bit RB4 à bas 
         
        }
        else if(!RB6) {
            RB4 = 1;
            __delay_us(800);
            RB4 = 0;
            __delay_us(19200);
        }
    }
    return 0;
}
