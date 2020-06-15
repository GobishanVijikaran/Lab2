//Actually, some hint, it might be one of the lab demo questions to update the code right on the fly to turn on/off another LED
//#define __O volatileoh 

#include <lpc17xx.h>
#include "stdio.h"
#include "uart.h"
#include <stdbool.h>

//part two 
// macro definitions (input pins found on MCB 1700 schematic)
#define JOYSTICKNORTH 23
#define JOYSTICKEAST 24
#define JOYSTICKSOUTH 25 
#define JOYSTICKWEST 26
#define JOYSTICKPRESS 20
#define MASK 0x1

int main(void){
	
	SystemInit(); 
	
	//pointing to block of registers for GPIO1 and output pins set in FIODIR (data direction resiter)
	LPC_GPIO1->FIODIR =((0<<JOYSTICKNORTH)); 
	LPC_GPIO1->FIODIR =((0<<JOYSTICKEAST));
	LPC_GPIO1->FIODIR =((0<<JOYSTICKSOUTH)); 
	LPC_GPIO1->FIODIR =((0<<JOYSTICKWEST)); 
	
	// infinite polling (keeps checking to see if data has been received)
	while(true){
		//FIOPIN used to read the pin 
		//logical condition: check if the joystick is pressed or not 
		if(!(LPC_GPIO1->FIOPIN>>JOYSTICKPRESS & MASK)){
			//checking for each direction of the joystick and printing out the position
			if(!(LPC_GPIO1->FIOPIN>>JOYSTICKNORTH & MASK)){
				printf("%s\n", "Joystick Position: North and Pressed"); 
			}
			else if(!(LPC_GPIO1->FIOPIN>>JOYSTICKEAST & MASK)){
				printf("%s\n", "Joystick Position: East and Pressed");
			}
			else if(!(LPC_GPIO1->FIOPIN>>JOYSTICKSOUTH & MASK)){
				printf("%s\n", "Joystick Position: South and Pressed");
			}
			else if(!(LPC_GPIO1->FIOPIN>>JOYSTICKWEST & MASK)){
				printf("%s\n", "Joystick Position: West and Pressed");
			}
			// add center positon 
		}
		else{
			if(!(LPC_GPIO1->FIOPIN>>JOYSTICKNORTH & MASK)){
				printf("%s\n", "Joystick Position: North and Not Pressed"); 
			}
			else if(!(LPC_GPIO1->FIOPIN>>JOYSTICKEAST & MASK)){
				printf("%s\n", "Joystick Position: East and Not Pressed");
			}
			else if(!(LPC_GPIO1->FIOPIN>>JOYSTICKSOUTH & MASK)){
				printf("%s\n", "Joystick Position: South and Not Pressed");
			}
			else if(!(LPC_GPIO1->FIOPIN>>JOYSTICKWEST & MASK)){
				printf("%s\n", "Joystick Position: West and Not Pressed");
			// add center positon 
			}
		}
	}
}
