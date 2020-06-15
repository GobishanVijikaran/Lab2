//Actually, some hint, it might be one of the lab demo questions to update the code right on the fly to turn on/off another LED
//#define __O volatileoh 

#include <lpc17xx.h>
#include "stdio.h"
#include "uart.h"
#include <stdbool.h>

//part two 
// macro definitions (pins found on MCB 1700 schematic)
#define JOYSTICKNORTH 23
#define JOYSTICKEAST 24
#define JOYSTICKSOUTH 25 
#define JOYSTICKWEST 26

int main(void){
	
	SystemInit(); 
	
	//pointing to block of registers for GPIO1 and output pins set in FIODIR
	LPC_GPIO1->FIODIR =((0<<JOYSTICKNORTH)); 
	LPC_GPIO1->FIODIR =((0<<JOYSTICKEAST));
	LPC_GPIO1->FIODIR =((0<<JOYSTICKSOUTH)); 
	LPC_GPIO1->FIODIR =((0<<JOYSTICKWEST)); 
	
	printf("hello world"); 
}
