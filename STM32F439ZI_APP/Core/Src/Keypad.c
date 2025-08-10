/*
 * Keypad.c
 *
 *  Created on: 27-Nov-2022
 *      Author: Jeshwanth NG
 */
#include "main.h"
#include "Keypad.h"
#include "gpio.h"

#define MAX_KEYPAD_ROWS (4)
#define MAX_KEYPAD_COLS (4)

xQueueHandle keypadQueue = NULL;


static uint8_t KeypadGetKeyPressed(void);

typedef enum ENUM_KEYPAD_STATES
{
	KEYPAD_STATE_INITIAL=0,
	KEYPAD_STATE_CHECK_DEBOUNCE,
	MAX_KEYPAD_STATES
}ENUM_KEYPAD_STATES;

typedef struct STRUCT_KEYPAD_ROW_IO
{
	GPIO_TypeDef* keypad_row_port;
	uint16_t      keypad_row_pin;
}STRUCT_KEYPAD_ROW_IO;

typedef struct STRUCT_KEYPAD_COL_IO
{
	GPIO_TypeDef* keypad_col_port;
	uint16_t      keypad_col_pin;
}STRUCT_KEYPAD_COL_IO;

STRUCT_KEYPAD_ROW_IO  key_row_io[MAX_KEYPAD_ROWS];
STRUCT_KEYPAD_COL_IO  key_col_io[MAX_KEYPAD_COLS];

void Initialize_Keypad(void)
{
	Write_Pin(KPD_ROW_1_PORT, KPD_ROW_1_PIN, GPIO_PIN_SET);
	Write_Pin(KPD_ROW_2_PORT, KPD_ROW_2_PIN, GPIO_PIN_SET);
	Write_Pin(KPD_ROW_3_PORT, KPD_ROW_3_PIN, GPIO_PIN_SET);
	Write_Pin(KPD_ROW_4_PORT, KPD_ROW_4_PIN, GPIO_PIN_SET);

	key_row_io[0].keypad_row_port = KPD_ROW_1_PORT;
	key_row_io[0].keypad_row_pin = KPD_ROW_1_PIN;
	key_row_io[1].keypad_row_port = KPD_ROW_2_PORT;
	key_row_io[1].keypad_row_pin = KPD_ROW_2_PIN;
	key_row_io[2].keypad_row_port = KPD_ROW_3_PORT;
	key_row_io[2].keypad_row_pin = KPD_ROW_3_PIN;
	key_row_io[3].keypad_row_port = KPD_ROW_4_PORT;
	key_row_io[3].keypad_row_pin = KPD_ROW_4_PIN;

	key_col_io[0].keypad_col_port = KPD_COL_1_PORT;
	key_col_io[0].keypad_col_pin = KPD_COL_1_PIN;
	key_col_io[1].keypad_col_port = KPD_COL_2_PORT;
	key_col_io[1].keypad_col_pin = KPD_COL_2_PIN;
	key_col_io[2].keypad_col_port = KPD_COL_3_PORT;
	key_col_io[2].keypad_col_pin = KPD_COL_3_PIN;
	key_col_io[3].keypad_col_port = KPD_COL_4_PORT;
	key_col_io[3].keypad_col_pin = KPD_COL_4_PIN;

	keypadQueue = xQueueCreate(15, sizeof(KEYPAD_CODES));
}

KEYPAD_CODES keypad_look_up[MAX_KEYPAD_ROWS][MAX_KEYPAD_COLS] = { {KEY_CLEAR,  KEY_THREE,   KEY_TWO,  KEY_ONE},
		                         	 	 	 	 	 	 	 {KEY_LOGIN,  KEY_SIX,   KEY_FIVE,  KEY_FOUR},
															 {KEY_CMD,  KEY_NINE,   KEY_EIGHT,  KEY_SEVEN},
															 {KEY_ENTER,  KEY_HASH,  KEY_ZERO,  KEY_STAR}
                               	   	   	   	   	   	   	   };

static uint8_t KeypadGetKeyPressed(void)
{
	uint8_t key_row_index = 0;
	uint8_t key_col_index = 0;
	KEYPAD_CODES column_data = KEY_NOT_PRESSED;

	column_data = KEY_NOT_PRESSED;
	for(key_row_index = 0; key_row_index < MAX_KEYPAD_ROWS; key_row_index++)
	{
		//Clear each row pin at a time and read all the corresponding column pins
		Write_Pin(key_row_io[key_row_index].keypad_row_port, key_row_io[key_row_index].keypad_row_pin, GPIO_PIN_RESET);
		for(key_col_index = 0; key_col_index < MAX_KEYPAD_COLS; key_col_index++)
		{
			if(!Read_Pin(key_col_io[key_col_index].keypad_col_port, key_col_io[key_col_index].keypad_col_pin))
			{
				//Key pressed
				column_data = keypad_look_up[key_row_index][key_col_index];
				break;
			}
		}
		Write_Pin(key_row_io[key_row_index].keypad_row_port, key_row_io[key_row_index].keypad_row_pin, GPIO_PIN_SET);
	}

	return column_data;
}

void KeypadTask(void const * argument)
{
	KEYPAD_CODES pressed_key = KEY_NOT_PRESSED;
	KEYPAD_CODES previous_key = KEY_NOT_PRESSED;
	static ENUM_KEYPAD_STATES keypad_state = KEYPAD_STATE_INITIAL;

	for(;;)
	{
		osDelay(50);
		switch(keypad_state)
		{
		case KEYPAD_STATE_INITIAL:
		{
			previous_key = KeypadGetKeyPressed();
			if(previous_key != KEY_NOT_PRESSED)
			{
				keypad_state = KEYPAD_STATE_CHECK_DEBOUNCE;
			}
		}
		break;
		case KEYPAD_STATE_CHECK_DEBOUNCE:
		{
			pressed_key = KeypadGetKeyPressed();
			if(pressed_key == previous_key)
			{
				//Presses key valid after debounce
				//Post a message
			    xQueueSend(keypadQueue, (void*)&pressed_key, 0);

			}
			previous_key = KEY_NOT_PRESSED;
			keypad_state = KEYPAD_STATE_INITIAL;

		}
		break;
		default:
		{

		}
		break;
		}
	}

}
