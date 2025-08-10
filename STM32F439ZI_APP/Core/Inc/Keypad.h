/*
 * Keypad.h
 *
 *  Created on: 27-Nov-2020
 *      Author: 600034585
 */

#ifndef INC_KEYPAD_H_
#define INC_KEYPAD_H_

typedef enum KEYPAD_CODES
{
	KEY_ZERO = 0,
	KEY_ONE,
	KEY_TWO,
	KEY_THREE,
	KEY_FOUR,
	KEY_FIVE,
	KEY_SIX,
	KEY_SEVEN,
	KEY_EIGHT,
	KEY_NINE,
	KEY_STAR,
	KEY_HASH,
	KEY_CLEAR,
	KEY_LOGIN,
	KEY_CMD,
	KEY_ENTER,
	KEY_NOT_PRESSED = 254,
	MAX_KEYPAD_KEYS

}KEYPAD_CODES;

#define KPD_ROW_1_PORT (GPIOD)
#define KPD_ROW_1_PIN  (GPIO_PIN_8)

#define KPD_ROW_2_PORT (GPIOA)
#define KPD_ROW_2_PIN  (GPIO_PIN_5)

#define KPD_ROW_3_PORT (GPIOA)
#define KPD_ROW_3_PIN  (GPIO_PIN_12)

#define KPD_ROW_4_PORT (GPIOA)
#define KPD_ROW_4_PIN  (GPIO_PIN_6)

#define KPD_COL_1_PORT (GPIOA)
#define KPD_COL_1_PIN  (GPIO_PIN_11)

#define KPD_COL_2_PORT (GPIOB)
#define KPD_COL_2_PIN  (GPIO_PIN_11)

#define KPD_COL_3_PORT (GPIOB)
#define KPD_COL_3_PIN  (GPIO_PIN_12)

#define KPD_COL_4_PORT (GPIOB)
#define KPD_COL_4_PIN  (GPIO_PIN_4)

void Initialize_Keypad(void);
uint8_t KeypadGetKey(void);
void KeypadTask(void const * argument);

#endif /* INC_KEYPAD_H_ */
