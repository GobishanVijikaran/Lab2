// Gobishan Vijikaran ---- 20783081
// Hunnain Atif ---------- 20780754

#include <lpc17xx.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define part 4

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

//part three
// macro definitions
#define LEDPIN0 28
#define LEDPIN1 29
#define LEDPIN2 31
#define LEDPIN3 2
#define LEDPIN4 3
#define LEDPIN5 4
#define LEDPIN6 5
#define LEDPIN7 6


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
#elif part == 3
int main(void){
	//clearing the bits
	LPC_GPIO1->FIODIR |= 0xB0000000;
	LPC_GPIO2->FIODIR |= 0x0000007C;
	
	char input[100]; // set up a var to take the users input
	int inputAsInt; // set up a var to store converted user input
	int bitArray[8] = {0}; // array to store bits of 8 digit binary number
	SystemInit(); // configure Clock and PLL
	

	printf("Enter value from 0 to 255: "); // prompt for user to enter their desired number
	scanf("%s", input); // registering input from user
	
	//checking to see if the input includes any letters using ANCII 
	//implementation of isDigit() function which is not availble in C99
	for (int j=0;j<strlen(input);j++){
		int ANCII_number = (int) input[j];
		if (ANCII_number>57 || ANCII_number<48) {
			printf("input has letters or is negative; choose number between 0 and 255\n");
		  return EXIT_FAILURE;
		}
	}
	
	//converting input into int 
	inputAsInt = atoi(input);
	
	//checking to see if int is in range fro 8-bit conversion
	if(inputAsInt < 0 || inputAsInt > 255){
		printf("number out of range; choose between 0 and 255\n");
		return EXIT_FAILURE;
	}
	
	//itterating though preset bit array and setting bits based on remainder
	int currPos = 0;
	while(inputAsInt > 0) {
		bitArray[currPos] = inputAsInt % 2;
		inputAsInt = inputAsInt / 2;
		currPos ++;
	}
	
	//Setting LEDS based on status of bits in array
	LPC_GPIO1->FIOSET = bitArray[0]<<LEDPIN0;
	LPC_GPIO1->FIOSET = bitArray[1]<<LEDPIN1;
	LPC_GPIO1->FIOSET = bitArray[2]<<LEDPIN2;
	LPC_GPIO2->FIOSET = bitArray[3]<<LEDPIN3;
	LPC_GPIO2->FIOSET = bitArray[4]<<LEDPIN4;
	LPC_GPIO2->FIOSET = bitArray[5]<<LEDPIN5;
	LPC_GPIO2->FIOSET = bitArray[6]<<LEDPIN6;
	LPC_GPIO2->FIOSET = bitArray[7]<<LEDPIN7;
}

#elif part == 4
// part 4 (ADC) 
int main(void){
	SystemInit(); 
//initialization (setting bit 12/adc bit)
	
	LPC_SC->PCONP |= (MASK << 12); 
	
	//set the pin select register (as analog rather than GPIO)
	//clear bit 
	LPC_PINCON->PINSEL1 &= ~(0x03 << 18); 
	LPC_PINCON->PINSEL1 |= (MASK << 18); 
	
	//set ADCR for correct input (potentiometer pin 2)
	// using bits 8-15 as an 8 bit binrary # to represent the divisor 
	//enable the adcr circuitry (enable bit = 21)
	LPC_ADC->ADCR = (1 << 2)|(4 << 8)|(1 << 21);
	
// reading the adc 
	
	while (true) {
		
		// begin conversion
		LPC_ADC->ADCR |= (1 << 24);
		
		while ((LPC_ADC->ADGDR & 0x1000000000) != 0);
		int adc_val = (LPC_ADC->ADGDR & (0xFFF << 4)) >> 4; // 4 bit shift to the right, & with bit mask 
		printf("Converted Value: %d\n", adc_val);
	}

}

#endif
