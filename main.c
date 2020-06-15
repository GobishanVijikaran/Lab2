
//#define __O volatileoh 

#include <lpc17xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define part 1

//part one
// macro definitions
#define LEDPIN 6
#define SWITCHPIN 10


//part two 
// macro definitions (input pins found on MCB 1700 schematic)
#define JOYSTICKNORTH 23
#define JOYSTICKEAST 24
#define JOYSTICKSOUTH 25 
#define JOYSTICKWEST 26
#define JOYSTICKPRESS 20
#define MASK 0x01


#if part == 1
int main(void){
	uint32_t currStatus; // set car for holding current status of switch
	SystemInit(); // configure Clock and PLL
	LPC_GPIO2->FIODIR =(0<<SWITCHPIN);// shift left by 10 and write 0 to that location
	LPC_GPIO2->FIODIR =(1<<LEDPIN);// shift left by 6 and write 1 to that location
	
	while(true){ // keep looping forever
		currStatus = (LPC_GPIO2->FIOPIN & (1<<SWITCHPIN)); // check to see if the switch is pressed or not
		if(!currStatus){ // if switch is pressed
			LPC_GPIO2->FIOSET |=(1<<LEDPIN); //set the bits using an OR to turn on the LED
		}
		else{
			LPC_GPIO2->FIOCLR =(1<<LEDPIN); //clear the output bit to 0
		}
	}
}
	

#elif part == 2
int main(void){
	
	SystemInit(); 
	
	//pointing to block of registers for GPIO1 and output pins set in FIODIR (data direction resiter) to indicate that the pins are inputs

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
			else{
				printf("%s\n", "Joystick Position: Center and Pressed");
			}
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
			}
			else{
				printf("%s\n", "Joystick Position: Center and Not Pressed");
			}
		}
	}
}


#elif part == 4
// part 4 (ADC) 
int main(void){
	SystemInit(); 
//initialization (setting bit 12/adc bit)
	
	LPC_SC->PCONP |= (1 << 12); 
	
	//set the pin select register (as analog rather than GPIO)
	//clear bit 
	LPC_PINCON->PINSEL1 &= ~(0x03 << 18); 
	LPC_PINCON->PINSEL1 |= (MASK << 18); 
	
	//set ADCR for correct input (potentiometer pin 2)
	LPC_ADC->ADCR |= (1 << 2);
	// using bits 8-15 as an 8 bit binrary # to represent the divisor 
	LPC_ADC->ADCR |= (4 << 8);
	//enable the adcr circuitry (enable bit = 21)
	LPC_ADC->ADCR |= (1<<21); 
	
// reading the adc 
	while(true){
		//set bit 24 of the ADCR to start conversion 
		LPC_ADC->ADCR |= (1 << 24); 
		//waiting for bit 31 of the adgdr to indicate coversion complete 
		while((LPC_ADC->ADCR & 0x1000000000) != 0);
			// adgdr contains the converted value 
		uint16_t ADGDR_val = (LPC_ADC->ADGDR>>4)&0xFFF; 
		printf("Value: %d\n", ADGDR_val); 
	}
}

#endif
