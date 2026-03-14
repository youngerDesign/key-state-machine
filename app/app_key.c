#include "app_key.h"

#include "delay.h"

DDA_Err_t KeyInit(void)
{
	DDA_Err_t err = DDA_OK;
	GPIO_Config_t config = {0}; // 这一步全部初始化为0是必须的，否则pinMask的值不确定，碰到过把LED灯配置改了，导致黄灯亮度非常低

	GPIO_ClockEnable(GPIO_GROUPA, TRUE);
	
	config.group = GPIO_GROUPA;
	config.pinMask |= (1<<GPIO_PIN0);
	config.mode = GPIO_Mode_PULL;
	config.directionSpeed = GPIO_INPUT_MODE;
	config.defaultLevel = GPIO_PIN_LEVEL_LOW; // 下拉输入
	err = GPIO_Config(&config);	
	
	GPIO_ClockEnable(GPIO_GROUPE, TRUE);
	
	config.group = GPIO_GROUPE;
	config.defaultLevel = GPIO_PIN_LEVEL_HIGH; // 上拉输入

	config.pinMask = 0; // 注意：用同一个变量，用之前一定要先清空之前置的标志位
	config.pinMask |= (1<<GPIO_PIN2);
	config.pinMask |= (1<<GPIO_PIN3);
	config.pinMask |= (1<<GPIO_PIN4);
	err = GPIO_Config(&config);
	
	return (err);
}

DDA_Err_t KeyExtiInit(void)
{
	DDA_Err_t err = DDA_OK;
	err = KeyInit(); //IO口的配置与按键配置一样

	if (err != DDA_OK) {
		return (err);
	}

	GPIO_ExtiConfig_t extiConfig = {0};
	extiConfig.group = GPIO_GROUPA;
	extiConfig.pinMask |= (1<<GPIO_PIN0);
	extiConfig.triggerMode = DOUBLE_EDGE_TRIGGER;
	err = GPIO_ExtiConfig(&extiConfig);
	MY_NVIC_Init(2,3,EXTI0_IRQn,2);	//抢占2，子优先级3，组2
	
	extiConfig.group = GPIO_GROUPE;
	extiConfig.pinMask = 0; // 注意：用同一个变量，用之前一定要先清空之前置的标志位
	extiConfig.pinMask |= (1<<GPIO_PIN2);
	extiConfig.pinMask |= (1<<GPIO_PIN3);
	extiConfig.pinMask |= (1<<GPIO_PIN4);
	extiConfig.triggerMode = FALLING_EDGE_TRIGGER;
	err = GPIO_ExtiConfig(&extiConfig);
	MY_NVIC_Init(2,2,EXTI2_IRQn,2);	//抢占2，子优先级2，组2	   
	MY_NVIC_Init(2,1,EXTI3_IRQn,2);	//抢占2，子优先级1，组2	   
	MY_NVIC_Init(2,0,EXTI4_IRQn,2);	//抢占2，子优先级0，组2	
	
	return (err);
}

DDA_Err_t Key0ExtiInit(void)
{
	DDA_Err_t err = DDA_OK;
	
	GPIO_Config_t config = {0}; // 这一步全部初始化为0是必须的，否则pinMask的值不确定，碰到过把LED灯配置改了，导致黄灯亮度非常低
	GPIO_ClockEnable(GPIO_GROUPE, TRUE);
	config.group = GPIO_GROUPE;
	config.pinMask |= (1<<GPIO_PIN4);
	config.mode = GPIO_Mode_PULL;
	config.directionSpeed = GPIO_INPUT_MODE;
	config.defaultLevel = GPIO_PIN_LEVEL_HIGH; // 上拉输入
	err = GPIO_Config(&config);	
	//err = KeyInit(); //IO口的配置与按键配置一样
	
	GPIO_ExtiConfig_t extiConfig = {0};
	extiConfig.group = GPIO_GROUPE;
	extiConfig.pinMask |= (1<<GPIO_PIN4);
	extiConfig.triggerMode = DOUBLE_EDGE_TRIGGER;
	err = GPIO_ExtiConfig(&extiConfig);
	MY_NVIC_Init(2,0,EXTI4_IRQn,2);	//抢占2，子优先级0，组2	
	
	return (err);
}

u8 KEY_Scan(u8 mode)
{
	static u8 key_up=1;//按键按松开标志
	if(mode)key_up=1; //支持连按 
	if(key_up&&(KEY0==0||KEY1==0||KEY2==0||WK_UP==1))
	{
		delay_ms(10);//去抖动
		key_up=0;
		if(KEY0==0)return 1;
		else if(KEY1==0)return 2;
		else if(KEY2==0)return 3;
		else if(WK_UP==1)return 4;
	}else if(KEY0==1&&KEY1==1&&KEY2==1&&WK_UP==0) {
		key_up=1;
	}		
	return 0;// 无按键按下
}

uint8_t KeyLevelRead(void)
{
	return(GPIO_PinReadPin(GPIO_GROUPA, GPIO_PIN0));
}

