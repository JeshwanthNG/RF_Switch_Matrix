/*
 * rfswitch.h
 *
 *  Created on: Nov 29, 2020
 *      Author: 600034585
 */

#ifndef INC_RFSWITCH_H_
#define INC_RFSWITCH_H_

/*
 GPIO MAPPING FOR SWITCHES
    INPUT             OUTPUT
 -----------       -----------
 Switch1 PC11       Switch5 PB1
 	     PC10       	    PB2
 	     PD2      	        PB3
 	     PC12       	    PB4

 Switch2           Switch6
         PB5               PB5
         PB6               PB6
         PB7               PB7
         PB8               PB8

 Switch3           Switch7
 	 	 PB9       	 	   PB9
 	 	 PB10      	 	   PB10
 	 	 PB11      	 	   PB11
 	 	 PB12      	 	   PB12

 Switch4           Switch8
 	 	 PC1       	 	   PC1
 	 	 PC2       	 	   PC2
 	 	 PC3       	 	   PC3
 	 	 PC4       	 	   PC4

 *
 */

#define MAX_IN_OUT_SWITCHES (4)

//Switch 1 GPIO
#define SW1_PIN1_PORT	GPIOC
#define SW1_PIN1_PIN  	GPIO_PIN_11
#define SW1_PIN2_PORT	GPIOC
#define SW1_PIN2_PIN  	GPIO_PIN_10
#define SW1_PIN3_PORT	GPIOD
#define SW1_PIN3_PIN  	GPIO_PIN_2
#define SW1_PIN4_PORT	GPIOC
#define SW1_PIN4_PIN  	GPIO_PIN_12
//Switch 2 GPIO
#define SW2_PIN1_PORT	GPIOF
#define SW2_PIN1_PIN  	GPIO_PIN_6
#define SW2_PIN2_PORT	GPIOF
#define SW2_PIN2_PIN  	GPIO_PIN_7
#define SW2_PIN3_PORT	GPIOA
#define SW2_PIN3_PIN  	GPIO_PIN_15
#define SW2_PIN4_PORT	GPIOC
#define SW2_PIN4_PIN  	GPIO_PIN_13
//Switch 3 GPIO
#define SW3_PIN1_PORT	GPIOA
#define SW3_PIN1_PIN  	GPIO_PIN_0
#define SW3_PIN2_PORT	GPIOA
#define SW3_PIN2_PIN  	GPIO_PIN_4
#define SW3_PIN3_PORT	GPIOB
#define SW3_PIN3_PIN  	GPIO_PIN_0
#define SW3_PIN4_PORT	GPIOC
#define SW3_PIN4_PIN  	GPIO_PIN_2
//Switch 4 GPIO
#define SW4_PIN1_PORT	GPIOC
#define SW4_PIN1_PIN  	GPIO_PIN_0
#define SW4_PIN2_PORT	GPIOC
#define SW4_PIN2_PIN  	GPIO_PIN_3
#define SW4_PIN3_PORT	GPIOD
#define SW4_PIN3_PIN  	GPIO_PIN_3
#define SW4_PIN4_PORT	GPIOD
#define SW4_PIN4_PIN  	GPIO_PIN_7




typedef struct STRUCT_RF_SWITCH
{
	uint8_t input_switches;
	uint8_t output_switches;
}STRUCT_RF_SWITCH;

void SwitchMatrixInitialize(void);
uint8_t SwitchSetInput(uint8_t inputSwNum, uint8_t outputSwNum);
uint8_t SwitchSetOutput(uint8_t outputSwNum, uint8_t inputSwNum);
uint8_t SwitchReadInput(uint8_t inputSwNum, uint8_t* outputSwNum);
uint8_t SwitchReadOuput(uint8_t outputSwNum, uint8_t* inputSwNum);
void SwitchReadAllSwitches(STRUCT_RF_SWITCH* Inputs);



#endif /* INC_RFSWITCH_H_ */
