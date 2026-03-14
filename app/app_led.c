#include "app_led.h"
#include "app_softTimer.h"
#include "usart.h"

void LedInit(void)
{
	GPIO_ClockEnable(GPIO_GROUPB, TRUE);
	GPIO_ClockEnable(GPIO_GROUPE, TRUE);
	
	GPIO_Config_t config = {0};
	config.group = GPIO_GROUPB; // ºìµÆ
	config.pinMask |= (1<<GPIO_PIN5);
	config.mode = GPIO_Mode_PUSH_PULL;
	config.directionSpeed = GPIO_OUTPUT_MODE_SPEED50MHZ;
	config.defaultLevel = GPIO_PIN_LEVEL_HIGH;
	GPIO_Config(&config);
	
	config.group = GPIO_GROUPE; // »ÆµÆ
	GPIO_Config(&config);
}

uint8_t g_ledState = 0;
DDA_Timer_t *g_ledTimer;
void APP_LedTimerCallback(void)
{
	if (g_ledState == 0) {
		GPIO_PinWritePin(GPIO_GROUPE, GPIO_PIN5, 0);
		g_ledState = 1;
	} else {
		GPIO_PinWritePin(GPIO_GROUPE, GPIO_PIN5, 1);
		g_ledState = 0;
	}
}

void APP_RedLedBlinkInit(void)
{
	LedInit();
	g_ledTimer = DDA_TimerCreate(APP_LedTimerCallback, 1, 1010);
	DDA_TimerStart(g_ledTimer);
}


