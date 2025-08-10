/*
 * lcd.h
 *
 *  Created on: 27-Nov-2020
 *      Author: 600034585
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_



#define LCD_RS_PORT (GPIOC)
#define LCD_RS_PIN  (GPIO_PIN_8)

#define LCD_EN_PORT (GPIOC)
#define LCD_EN_PIN  (GPIO_PIN_9)

#define LCD_D4_PORT (GPIOC)
#define LCD_D4_PIN  (GPIO_PIN_6)

#define LCD_D5_PORT (GPIOB)
#define LCD_D5_PIN  (GPIO_PIN_8)

#define LCD_D6_PORT (GPIOB)
#define LCD_D6_PIN  (GPIO_PIN_2)

#define LCD_D7_PORT (GPIOB)
#define LCD_D7_PIN  (GPIO_PIN_9)


void LcdPutString(uint8_t x, uint8_t y, const char *strPtr);
void LcdPutByte(uint8_t x, uint8_t y, char byte);
void LcdClear(void);
void LcdInitialize(void);

#endif /* INC_LCD_H_ */
