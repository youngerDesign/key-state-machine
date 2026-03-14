#include "sys.h"
#include "usart.h"
#include "delay.h"

#include "app_led.h"
#include "app_softTimer.h"
#include "app_keyStateMachine.h"



void APP_TestThreadEntry(void);

int main(void)
{

	Stm32_Clock_Init(9); //系统时钟设置
	delay_init(72); //延时初始化
	uart_init(72,115200); //串口初始化为 115200

	SoftTimerInit();
	APP_RedLedBlinkInit();
	KeyStateMachineInit();
	
	while(1)
	{
		APP_KeyThreadEntry();
		APP_TestThreadEntry();
	}
}

void APP_TestThreadEntry(void)
{
	switch (g_keyMessageQueue) {
		case 0: 
			//printf("key value:%d'r'n", g_keyMessageQueue);
			break;
		case 1: 
			printf("press key value:%d\r\n", g_keyMessageQueue);
			break;
		case 2: 
			printf("repeatPress key value:%d\r\n", g_keyMessageQueue);
			break;
		case 3: 
			printf("repeatPress key value:%d\r\n", g_keyMessageQueue);
			break;
		case 4: 
			printf("repeatPress key value:%d\r\n", g_keyMessageQueue);
			break;
		case 5: 
			printf("repeatPress key value:%d\r\n", g_keyMessageQueue);
			break;
		case 20: 
			printf("longPress key value:%d\r\n", g_keyMessageQueue);
			break;
		case 21: 
			printf("longPress key value:%d\r\n", g_keyMessageQueue);
			break;
		default:
			printf("err key value:%d\r\n", g_keyMessageQueue);
	}
	g_keyMessageQueue = 0;
}
