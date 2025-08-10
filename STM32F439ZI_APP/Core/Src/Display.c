/*
 * Display.c
 *
 *  Created on: Nov 28, 2020
 *      Author: 600034585
 */
#include "main.h"
#include "lcd.h"
#include "gpio.h"
#include "keypad.h"
#include "rfswitch.h"

#define MAX_DISPLAY_STRINGS (10)
#define MAX_SCREENS         (10)
#define MAX_COL_LCD         (20)

static void ScreenStartUp(void);
static void ScreenSwitchStatus(void);
static void ScreenMenu(void);
static void ScreenSwitchSettings(void);
static void ScreenEthernetSettings(void);
static void ScreenBaudSettings(void);
static void ScreenSlaveSettings(void);


const char *screen_menu_strings[4] =
{
		"1 Switch Settings   ",
		"2 Ethernet Settings ",
		"3 Baud Settings     ",
		"4 Slave Settings    "
};

const char *screen_startup_strings[3] =
{
		" TIRANGA AEROSPACE  ", //0
		" RF SWITCH MATRIX   ", //1
		"    Version 1.0     " //2
};

typedef enum ENUM_LCD_SCREENS
{
	SCREEN_STARTUP,
	SCREEN_SWITCH_STATUS,
	SCREEN_MENU,
	SCREEN_SWITCH_SETTINGS,
	SCREEN_ETHERNET_SETTINGS,
	SCREEN_BAUD_STTINGS,
	SCREEN_SLAVE_SETTINGS,
	MAX_LCD_SCREENS
}ENUM_LCD_SCREENS;

void (*screenFunctions[MAX_SCREENS])(void) =
{
		ScreenStartUp,
		ScreenSwitchStatus,
		ScreenMenu,
		ScreenSwitchSettings,
		ScreenEthernetSettings,
		ScreenBaudSettings,
		ScreenSlaveSettings

};

static ENUM_LCD_SCREENS currentScreen = SCREEN_STARTUP;
static char lcd_buf[MAX_COL_LCD];

extern xQueueHandle keypadQueue;
portBASE_TYPE result;
KEYPAD_CODES keypadCode;

void DisplayTask(void const * argument)
{

	LcdInitialize();
	for(;;)
	{
		osDelay(500);
		screenFunctions[currentScreen]();
		TOGGLE_LED_PB14();
	}
}

//SCREEN_STARTUP
static void ScreenStartUp(void)
{
	static uint8_t firsttime = true;
	static uint8_t delaycounter = 0;

	if(firsttime)
	{
		firsttime = false;
		LcdPutString(1, 1,screen_startup_strings[0]);
		LcdPutString(2, 1,screen_startup_strings[1]);
		LcdPutString(3, 1,screen_startup_strings[2]);
	}
	else
	{
		if(delaycounter++ > 4)
		{
			delaycounter = 0;
			LcdClear();
			currentScreen = SCREEN_SWITCH_STATUS;
		}
	}
}

//SCREEN_SWITCH_STATUS
static void ScreenSwitchStatus(void)
{
	STRUCT_RF_SWITCH rf_sw_config[MAX_IN_OUT_SWITCHES];
	static uint8_t firsttime = true;
	if(firsttime)
	{
		firsttime = false;
		SwitchReadAllSwitches(&rf_sw_config[0]);
		sprintf(lcd_buf,"Current   In1->Out%u",rf_sw_config[0].input_switches);
		LcdPutString(1, 1,lcd_buf);
		sprintf(lcd_buf,"Switch    In2->Out%u",rf_sw_config[1].input_switches);
		LcdPutString(2, 1,lcd_buf);
		sprintf(lcd_buf,"Status    In3->Out%u",rf_sw_config[2].input_switches);
		LcdPutString(3, 1,lcd_buf);
		sprintf(lcd_buf,"          In4->Out%u",rf_sw_config[3].input_switches);
		LcdPutString(4, 1,lcd_buf);

	}
	else
	{
		if(xQueueReceive(keypadQueue, &keypadCode, 0))
		{
			if(keypadCode == KEY_LOGIN)
			{
				LcdClear();
				currentScreen = SCREEN_MENU;
			}
		}
	}
}

//SCREEN_MENU
static void ScreenMenu(void)
{
	static uint8_t firsttime = true;
	if(firsttime)
	{
		firsttime = false;
		LcdPutString(1, 1,screen_menu_strings[0]);
		LcdPutString(2, 1,screen_menu_strings[1]);
		LcdPutString(3, 1,screen_menu_strings[2]);
		LcdPutString(4, 1,screen_menu_strings[3]);
	}
	else
	{
		if(xQueueReceive(keypadQueue, &keypadCode, 0))
		{
			if(keypadCode > KEY_ZERO && keypadCode < KEY_FIVE)
			{
				LcdClear();
				firsttime = true;
				currentScreen = SCREEN_MENU + keypadCode;
			}
		}
	}
}

//SCREEN_SWITCH_SETTINGS
static void ScreenSwitchSettings(void)
{
	static uint8_t firsttime = true;
	if(firsttime)
	{
		firsttime = false;
		LcdPutString(1, 1,"Switch Settings");
		Write_Pin(SW4_PIN1_PORT, SW4_PIN1_PIN, GPIO_PIN_SET);
		Write_Pin(SW4_PIN2_PORT, SW4_PIN2_PIN, GPIO_PIN_SET);
		Write_Pin(SW4_PIN3_PORT, SW4_PIN3_PIN, GPIO_PIN_SET);
		Write_Pin(SW4_PIN4_PORT, SW4_PIN4_PIN, GPIO_PIN_SET);
	}
	else
	{
		if(xQueueReceive(keypadQueue, &keypadCode, 0))
		{
			if(keypadCode == KEY_LOGIN)
			{
				LcdClear();
				firsttime = true;
				currentScreen = SCREEN_MENU;
			}
		}
	}
}

//SCREEN_ETHERNET_SETTINGS
static void ScreenEthernetSettings(void)
{
	static uint8_t firsttime = true;
	if(firsttime)
	{
		firsttime = false;
		LcdPutString(1, 1,"Ethernet Settings");
		Write_Pin(SW4_PIN1_PORT, SW4_PIN1_PIN, GPIO_PIN_RESET);
		Write_Pin(SW4_PIN2_PORT, SW4_PIN2_PIN, GPIO_PIN_RESET);
		Write_Pin(SW4_PIN3_PORT, SW4_PIN3_PIN, GPIO_PIN_RESET);
		Write_Pin(SW4_PIN4_PORT, SW4_PIN4_PIN, GPIO_PIN_RESET);
	}
	else
	{
		if(xQueueReceive(keypadQueue, &keypadCode, 0))
		{
			if(keypadCode == KEY_LOGIN)
			{
				LcdClear();
				firsttime = true;
				currentScreen = SCREEN_MENU;
			}
		}
	}
}

//SCREEN_BAUD_STTINGS
static void ScreenBaudSettings(void)
{
	static uint8_t firsttime = true;
	if(firsttime)
	{
		firsttime = false;
		LcdPutString(1, 1,"Baud Settings");
	}
	else
	{
		if(xQueueReceive(keypadQueue, &keypadCode, 0))
		{
			if(keypadCode == KEY_LOGIN)
			{
				LcdClear();
				firsttime = true;
				currentScreen = SCREEN_MENU;
			}
		}
	}
}

//SCREEN_SLAVE_SETTINGS
static void ScreenSlaveSettings(void)
{
	static uint8_t firsttime = true;
	if(firsttime)
	{
		firsttime = false;
		LcdPutString(1, 1,"Slave Settings");
	}
	else
	{
		if(xQueueReceive(keypadQueue, &keypadCode, 0))
		{
			if(keypadCode == KEY_LOGIN)
			{
				LcdClear();
				firsttime = true;
				currentScreen = SCREEN_MENU;
			}
		}
	}
}



