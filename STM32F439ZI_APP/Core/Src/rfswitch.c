/*
 * rfswitch.c
 *
 *  Created on: Nov 29, 2020
 *      Author: 600034585
 */
#include "main.h"
#include "gpio.h"
#include "rfswitch.h"

static void SwitchInputSideControl(uint8_t swNum, uint8_t selecData);
static void SwitchOutputSideControl(uint8_t swNum, uint8_t selecData);

typedef enum ENUM_SWITCH_INPUT
{
	SW_IN_NUM_1 = 0,
	SW_IN_NUM_2,
	SW_IN_NUM_3,
	SW_IN_NUM_4,
	MAX_IN_SWITCHES
}ENUM_SWITCH_INPUT;

typedef enum ENUM_SWITCH_OUTPUT
{
	SW_OUT_NUM_1 = 0,
	SW_OUT_NUM_2,
	SW_OUT_NUM_3,
	SW_OUT_NUM_4,
	MAX_OUT_SWITCHES
}ENUM_SWITCH_OUTPUT;

static STRUCT_RF_SWITCH switch_configuration[MAX_IN_OUT_SWITCHES];

const uint8_t sw_num_to_port_map[MAX_IN_OUT_SWITCHES][MAX_IN_OUT_SWITCHES] =
  	  	  	  	  	  	  	  	  	{ {0x01,  0x02,   0x04,  0x08},
		                  	          {0x01,  0x02,   0x04,  0x08},
						              {0x01,  0x02,   0x04,  0x08},
						              {0x01,  0x02,   0x04,  0x08}
                                    };

static void SwitchGetInputData(uint8_t InputSwNum, uint8_t OutputSwNum, uint8_t* inData, uint8_t* outData)
{
	*inData = sw_num_to_port_map[InputSwNum][OutputSwNum];
	*outData = sw_num_to_port_map[OutputSwNum][InputSwNum];
}

static void SwitchGetOutputData(uint8_t OutputSwNum, uint8_t InputSwNum,  uint8_t* inData, uint8_t* outData)
{
	*inData = sw_num_to_port_map[OutputSwNum][InputSwNum];
	*outData = sw_num_to_port_map[InputSwNum][OutputSwNum];
}

void SwitchMatrixInitialize(void)
{
	//Default Switch connection
	//IN1 -> OUT1, IN2 -> OUT2, IN3 -> OUT3, IN4 -> OUT4

	switch_configuration[SW_IN_NUM_1].input_switches  = SW_OUT_NUM_1;
	switch_configuration[SW_OUT_NUM_1].output_switches = SW_IN_NUM_1;

	switch_configuration[SW_IN_NUM_2].input_switches  = SW_OUT_NUM_2;
	switch_configuration[SW_OUT_NUM_2].output_switches = SW_IN_NUM_2;

	switch_configuration[SW_IN_NUM_3].input_switches  = SW_OUT_NUM_3;
	switch_configuration[SW_OUT_NUM_3].output_switches = SW_IN_NUM_3;

	switch_configuration[SW_IN_NUM_4].input_switches  = SW_OUT_NUM_4;
	switch_configuration[SW_OUT_NUM_4].output_switches = SW_IN_NUM_4;
}



uint8_t SwitchSetInput(uint8_t inputSwNum, uint8_t outputSwNum)
{
	uint8_t returndata = false;
	uint8_t inputSwitchData;
	uint8_t outputSwitchData;
	if(inputSwNum > 0 && inputSwNum <= MAX_IN_OUT_SWITCHES &&
			outputSwNum > 0 && outputSwNum <= MAX_IN_OUT_SWITCHES)
	{
		inputSwNum -= 1;
		outputSwNum -= 1;
		SwitchGetInputData(inputSwNum, outputSwNum, &inputSwitchData, &outputSwitchData);
		SwitchInputSideControl(inputSwNum, inputSwitchData);
		SwitchOutputSideControl(outputSwNum, outputSwitchData);
		switch_configuration[inputSwNum].input_switches = outputSwNum;
		switch_configuration[outputSwNum].output_switches = inputSwNum;
		returndata = true;
	}
	return returndata;
}

uint8_t SwitchSetOutput(uint8_t outputSwNum, uint8_t inputSwNum)
{
	uint8_t returndata = false;
	uint8_t inputSwitchData;
	uint8_t outputSwitchData;
	if(inputSwNum > 0 && inputSwNum <= MAX_IN_OUT_SWITCHES &&
			outputSwNum > 0 && outputSwNum <= MAX_IN_OUT_SWITCHES)
	{
		inputSwNum -= 1;
		outputSwNum -= 1;
		SwitchGetOutputData(outputSwNum, inputSwNum,  &inputSwitchData, &outputSwitchData);
		SwitchOutputSideControl(outputSwNum, outputSwitchData);
		SwitchInputSideControl(inputSwNum, inputSwitchData);
		switch_configuration[outputSwNum].output_switches = inputSwNum;
		switch_configuration[inputSwNum].input_switches = outputSwNum;
		returndata = true;
	}
	return returndata;
}

uint8_t SwitchReadInput(uint8_t inputSwNum, uint8_t* outputSwNum)
{
	uint8_t returndata;
	if(inputSwNum > 0 && inputSwNum <=MAX_IN_OUT_SWITCHES)
	{
		inputSwNum -= 1;
		*outputSwNum = switch_configuration[inputSwNum].input_switches+1;
		returndata = true;
	}
	return returndata;
}

uint8_t SwitchReadOuput(uint8_t outputSwNum, uint8_t* inputSwNum)
{
	uint8_t returndata = false;
	if(outputSwNum > 0 && outputSwNum <=MAX_IN_OUT_SWITCHES)
	{
		outputSwNum -= 1;
		*inputSwNum = switch_configuration[outputSwNum].output_switches+1;
		returndata = true;
	}
	return returndata;
}

void SwitchReadAllSwitches(STRUCT_RF_SWITCH* Inputs)
{
	uint8_t index;
	for(index = 0; index < MAX_IN_OUT_SWITCHES; index++)
	{
		Inputs->input_switches = switch_configuration[index].input_switches+1;
		Inputs->output_switches = switch_configuration[index].output_switches+1;
		Inputs++;
	}
}

static void SwitchInputSideControl(uint8_t swNum, uint8_t selecData)
{
	switch(swNum)
	{
	case SW_IN_NUM_1:
	{
		Write_Pin(SW1_PIN1_PORT, SW1_PIN1_PIN, (selecData & 0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
		Write_Pin(SW1_PIN2_PORT, SW1_PIN2_PIN, (selecData & 0x02)?GPIO_PIN_SET:GPIO_PIN_RESET);
		Write_Pin(SW1_PIN3_PORT, SW1_PIN3_PIN, (selecData & 0x04)?GPIO_PIN_SET:GPIO_PIN_RESET);
		Write_Pin(SW1_PIN4_PORT, SW1_PIN4_PIN, (selecData & 0x08)?GPIO_PIN_SET:GPIO_PIN_RESET);

	}
	break;
	case SW_IN_NUM_2:
	{
		Write_Pin(SW2_PIN1_PORT, SW2_PIN1_PIN, (selecData & 0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
		Write_Pin(SW2_PIN2_PORT, SW2_PIN2_PIN, (selecData & 0x02)?GPIO_PIN_SET:GPIO_PIN_RESET);
		Write_Pin(SW2_PIN3_PORT, SW2_PIN3_PIN, (selecData & 0x04)?GPIO_PIN_SET:GPIO_PIN_RESET);
		Write_Pin(SW2_PIN4_PORT, SW2_PIN4_PIN, (selecData & 0x08)?GPIO_PIN_SET:GPIO_PIN_RESET);
	}
	break;
	case SW_IN_NUM_3:
	{
		Write_Pin(SW3_PIN1_PORT, SW3_PIN1_PIN, (selecData & 0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
		Write_Pin(SW3_PIN2_PORT, SW3_PIN2_PIN, (selecData & 0x02)?GPIO_PIN_SET:GPIO_PIN_RESET);
		Write_Pin(SW3_PIN3_PORT, SW3_PIN3_PIN, (selecData & 0x04)?GPIO_PIN_SET:GPIO_PIN_RESET);
		Write_Pin(SW3_PIN4_PORT, SW3_PIN4_PIN, (selecData & 0x08)?GPIO_PIN_SET:GPIO_PIN_RESET);
	}
	break;
	case SW_IN_NUM_4:
	{
		//Write_Pin()
		//Write_Pin()
		//Write_Pin()
		//Write_Pin()
	}
	break;
	default:
		break;
	}
}

static void SwitchOutputSideControl(uint8_t swNum, uint8_t selecData)
{
	switch(swNum)
	{
	case SW_OUT_NUM_1:
	{
		//Write_Pin()
		//Write_Pin()
		//Write_Pin()
		//Write_Pin()

	}
	break;
	case SW_OUT_NUM_2:
	{
		//Write_Pin()
		//Write_Pin()
		//Write_Pin()
		//Write_Pin()
	}
	break;
	case SW_OUT_NUM_3:
	{
		//Write_Pin()
		//Write_Pin()
		//Write_Pin()
		//Write_Pin()
	}
	break;
	case SW_OUT_NUM_4:
	{
		//Write_Pin()
		//Write_Pin()
		//Write_Pin()
		//Write_Pin()
	}
	break;
	default:
		break;
	}
}












