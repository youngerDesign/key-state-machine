#include "app_uart.h"
#include "gpio.h"


	
void Uart2Init(void)
{
	GPIO_ClockEnable(GPIO_GROUPA, TRUE);
	GPIO_Config_t config = {0};
	config.group = GPIO_GROUPA;
	config.pinMask |= (1<<GPIO_PIN2);
	config.mode = GPIO_Mode_REUSE_PUSH_PULL;
	config.directionSpeed = GPIO_OUTPUT_MODE_SPEED50MHZ;
	config.defaultLevel = GPIO_PIN_LEVEL_HIGH;
	GPIO_Config(&config);
	
	config.pinMask = 0;
	config.pinMask |= (1<<GPIO_PIN3);
	config.mode = GPIO_Mode_PULL;
	config.directionSpeed = GPIO_INPUT_MODE;
	GPIO_Config(&config);
	
	float temp;
	u16 fraction; 
	temp=(float)(36*1000000)/(115200); //波特率设置，可以理解为分频器，串口时钟是36M，36M/BRR=波特率

	UartConfig_t uartConfig;
	uartConfig.baudRate = temp;
	uartConfig.uartNum = UART_NUM2;
	UartConfig(uartConfig);
}

void Uart3Init(void)
{
	GPIO_ClockEnable(GPIO_GROUPB, TRUE);
	GPIO_Config_t config = {0};
	config.group = GPIO_GROUPB;
	config.pinMask |= (1<<GPIO_PIN10);
	config.mode = GPIO_Mode_REUSE_PUSH_PULL;
	config.directionSpeed = GPIO_OUTPUT_MODE_SPEED50MHZ;
	config.defaultLevel = GPIO_PIN_LEVEL_HIGH;
	GPIO_Config(&config);
	
	config.pinMask = 0;
	config.pinMask |= (1<<GPIO_PIN11);
	config.mode = GPIO_Mode_PULL;
	config.directionSpeed = GPIO_INPUT_MODE;
	GPIO_Config(&config);
	
	float temp;
	u16 fraction; 
	temp=(float)(36*1000000)/(115200); //波特率设置，可以理解为分频器，串口时钟是36M，36M/BRR=波特率

	UartConfig_t uartConfig;
	uartConfig.baudRate = temp;
	uartConfig.uartNum = UART_NUM3;
	UartConfig(uartConfig);
}

void Uart4Init(void)
{
	GPIO_ClockEnable(GPIO_GROUPC, TRUE);
	GPIO_Config_t config = {0};
	config.group = GPIO_GROUPC;
	config.pinMask |= (1<<GPIO_PIN10);
	config.mode = GPIO_Mode_REUSE_PUSH_PULL;
	config.directionSpeed = GPIO_OUTPUT_MODE_SPEED50MHZ;
	config.defaultLevel = GPIO_PIN_LEVEL_HIGH;
	GPIO_Config(&config);
	
	config.pinMask = 0;
	config.pinMask |= (1<<GPIO_PIN11);
	config.mode = GPIO_Mode_PULL;
	config.directionSpeed = GPIO_INPUT_MODE;
	GPIO_Config(&config);
	
	float temp;
	u16 fraction; 
	temp=(float)(36*1000000)/(115200); //波特率设置，可以理解为分频器，串口时钟是36M，36M/BRR=波特率

	UartConfig_t uartConfig;
	uartConfig.baudRate = temp;
	uartConfig.uartNum = UART_NUM4;
	UartConfig(uartConfig);
}


void Uart5Init(void)
{
	GPIO_ClockEnable(GPIO_GROUPC, TRUE);
	GPIO_Config_t config = {0};
	config.group = GPIO_GROUPC;
	config.pinMask |= (1<<GPIO_PIN12);
	config.mode = GPIO_Mode_REUSE_PUSH_PULL;
	config.directionSpeed = GPIO_OUTPUT_MODE_SPEED50MHZ;
	config.defaultLevel = GPIO_PIN_LEVEL_HIGH;
	GPIO_Config(&config);
	
	GPIO_ClockEnable(GPIO_GROUPD, TRUE);
	config.pinMask = 0;
	config.group = GPIO_GROUPD;
	config.pinMask |= (1<<GPIO_PIN2);
	config.mode = GPIO_Mode_PULL;
	config.directionSpeed = GPIO_INPUT_MODE;
	GPIO_Config(&config);
	
	float temp;
	u16 fraction; 
	temp=(float)(36*1000000)/(115200); //波特率设置，可以理解为分频器，串口时钟是36M，36M/BRR=波特率

	UartConfig_t uartConfig;
	uartConfig.baudRate = temp;
	uartConfig.uartNum = UART_NUM5;
	UartConfig(uartConfig);
}

