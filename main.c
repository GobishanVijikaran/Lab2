// Gobishan Vijikaran & Hunnain Atif

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
// macro definitions
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
	uint32_t currStatus; 
	SystemInit(); 
	
	LPC_GPIO2->FIODIR =(0<<SWITCHPIN);
	LPC_GPIO2->FIODIR =(1<<LEDPIN);
	
	while(true){ 
		currStatus = (LPC_GPIO2->FIOPIN & (1<<SWITCHPIN)); 
		if(!currStatus){ 
			LPC_GPIO2->FIOSET |=(1<<LEDPIN); 
		}
		else{
			LPC_GPIO2->FIOCLR =(1<<LEDPIN); 
		}
	}
}


#elif part == 2
int main(void){
	
	SystemInit(); 
	
	LPC_GPIO1->FIODIR =((0<<JOYSTICKNORTH)); 
	LPC_GPIO1->FIODIR =((0<<JOYSTICKEAST));
	LPC_GPIO1->FIODIR =((0<<JOYSTICKSOUTH)); 
	LPC_GPIO1->FIODIR =((0<<JOYSTICKWEST)); 
	
	while(true){
		if(!(LPC_GPIO1->FIOPIN>>JOYSTICKPRESS & MASK)){
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
	LPC_GPIO1->FIODIR |= 0xB0000000;
	LPC_GPIO2->FIODIR |= 0x0000007C;
	
	char input[100];
	int inputAsInt;
	int bitArray[8] = {0}; 
	SystemInit();
	

	printf("Enter value from 0 to 255: ");
	scanf("%s", input);
	
	for (int j=0;j<strlen(input);j++){
		int ANCII_number = (int) input[j];
		if (ANCII_number>57 || ANCII_number<48) {
			printf("input has letters or is negative; choose number between 0 and 255\n");
		  return EXIT_FAILURE;
		}
	}
	
	inputAsInt = atoi(input);

	if(inputAsInt < 0 || inputAsInt > 255){
		printf("number out of range; choose between 0 and 255\n");
		return EXIT_FAILURE;
	}
	
	int currPos = 0;
	while(inputAsInt > 0) {
		bitArray[currPos] = inputAsInt % 2;
		inputAsInt = inputAsInt / 2;
		currPos ++;
	}
	
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
//initialization 	
	LPC_SC->PCONP |= (MASK << 12); 

	LPC_PINCON->PINSEL1 &= ~(0x03 << 18); 
	LPC_PINCON->PINSEL1 |= (MASK << 18); 
	

	LPC_ADC->ADCR = (1 << 2)|(4 << 8)|(1 << 21);
	
// reading the adc 
	
	while (true) {
		
		// begin conversion
		LPC_ADC->ADCR |= (1 << 24);
		
		while ((LPC_ADC->ADGDR & 0x1000000000) != 0);
		int adc_val = (LPC_ADC->ADGDR & (0xFFF << 4)) >> 4; 
		printf("Converted Value: %d\n", adc_val);
	}

}

#endif
