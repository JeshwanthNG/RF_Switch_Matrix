/*
 * lcd.c
 *
 *  Created on: 27-Nov-2020
 *      Author: 600034585
 */
#include "main.h"
#include "lcd.h"
#include "gpio.h"


static void lcdEnable(void);
static void lcdCommand(char byte);
static void lcdData(char byte);


const static uint8_t lineaddres[4]={0x80,0xC0,0x94,0xD4};

static void lcdEnable(void)
{
	Write_Pin(LCD_EN_PORT,LCD_EN_PIN, GPIO_PIN_RESET);
	osDelay(2);
	Write_Pin(LCD_EN_PORT,LCD_EN_PIN, GPIO_PIN_SET);
}

static void lcdData(char byte)
{
	Write_Pin(LCD_RS_PORT,LCD_RS_PIN, GPIO_PIN_SET);
	Write_Pin(LCD_D4_PORT,LCD_D4_PIN, (byte & 0x10)?GPIO_PIN_SET:GPIO_PIN_RESET);
	Write_Pin(LCD_D5_PORT,LCD_D5_PIN, (byte & 0x20)?GPIO_PIN_SET:GPIO_PIN_RESET);
	Write_Pin(LCD_D6_PORT,LCD_D6_PIN, (byte & 0x40)?GPIO_PIN_SET:GPIO_PIN_RESET);
	Write_Pin(LCD_D7_PORT,LCD_D7_PIN, (byte & 0x80)?GPIO_PIN_SET:GPIO_PIN_RESET);
	lcdEnable();
	Write_Pin(LCD_D4_PORT,LCD_D4_PIN, (byte & 0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
	Write_Pin(LCD_D5_PORT,LCD_D5_PIN, (byte & 0x02)?GPIO_PIN_SET:GPIO_PIN_RESET);
	Write_Pin(LCD_D6_PORT,LCD_D6_PIN, (byte & 0x04)?GPIO_PIN_SET:GPIO_PIN_RESET);
	Write_Pin(LCD_D7_PORT,LCD_D7_PIN, (byte & 0x08)?GPIO_PIN_SET:GPIO_PIN_RESET);
	lcdEnable();
	osDelay(5);
}

static void lcdCommand(char byte)
{
	Write_Pin(LCD_RS_PORT,LCD_RS_PIN, GPIO_PIN_RESET);
	Write_Pin(LCD_D4_PORT,LCD_D4_PIN, (byte & 0x10)?GPIO_PIN_SET:GPIO_PIN_RESET);
	Write_Pin(LCD_D5_PORT,LCD_D5_PIN, (byte & 0x20)?GPIO_PIN_SET:GPIO_PIN_RESET);
	Write_Pin(LCD_D6_PORT,LCD_D6_PIN, (byte & 0x40)?GPIO_PIN_SET:GPIO_PIN_RESET);
	Write_Pin(LCD_D7_PORT,LCD_D7_PIN, (byte & 0x80)?GPIO_PIN_SET:GPIO_PIN_RESET);
	lcdEnable();
	Write_Pin(LCD_D4_PORT,LCD_D4_PIN, (byte & 0x01)?GPIO_PIN_SET:GPIO_PIN_RESET);
	Write_Pin(LCD_D5_PORT,LCD_D5_PIN, (byte & 0x02)?GPIO_PIN_SET:GPIO_PIN_RESET);
	Write_Pin(LCD_D6_PORT,LCD_D6_PIN, (byte & 0x04)?GPIO_PIN_SET:GPIO_PIN_RESET);
	Write_Pin(LCD_D7_PORT,LCD_D7_PIN, (byte & 0x08)?GPIO_PIN_SET:GPIO_PIN_RESET);
	lcdEnable();
	osDelay(5);
}

void LcdPutString(uint8_t x, uint8_t y, const char *strPtr)
{
   lcdCommand(lineaddres[x-1]+y-1);
   while(*strPtr)
   {
      lcdData(*strPtr++);
   }
}

void LcdPutByte(uint8_t x, uint8_t y, char byte)
{
   lcdCommand(lineaddres[x-1]+y-1);
   lcdData(((byte/10)|0x30));
   lcdData(((byte%10)|0x30));
}

void LcdClear(void)
{
   lcdCommand(0x01);
}


void LcdInitialize(void)
{
	Write_Pin(LCD_EN_PORT,LCD_EN_PIN, GPIO_PIN_SET);
	Write_Pin(LCD_RS_PORT,LCD_RS_PIN, GPIO_PIN_RESET);
	lcdCommand(0x33);
	lcdCommand(0x32);
	lcdCommand(0x28);
	lcdCommand(0x0C);
	lcdCommand(0x06);
	lcdCommand(0x01);
	osDelay(500);
}
