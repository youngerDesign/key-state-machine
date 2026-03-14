#include "app_timer.h"

DDA_Err_t Timer2Init(void)
{
	DDA_Err_t err = DDA_OK;
	TimerConfig_t timerConfig;
	timerConfig.num = TIMER2;
	timerConfig.mode = TIMER_MODE_PERIOD;
	timerConfig.unit = TIMER_UNIT_MS;
	timerConfig.timeout = 1000;
	err = TimerConfig(timerConfig);
	
	return (err);
}

DDA_Err_t Timer3Init(void)
{
	DDA_Err_t err = DDA_OK;
	TimerConfig_t timerConfig;
	timerConfig.num = TIMER3;
	timerConfig.mode = TIMER_MODE_ONCE;
	timerConfig.unit = TIMER_UNIT_S;
	timerConfig.timeout = 1;
	err = TimerConfig(timerConfig);
	
	return (err);
}

DDA_Err_t Timer4Init(void)
{
	DDA_Err_t err = DDA_OK;
	TimerConfig_t timerConfig;
	timerConfig.num = TIMER4;
	timerConfig.mode = TIMER_MODE_PERIOD;
	timerConfig.unit = TIMER_UNIT_S;
	timerConfig.timeout = 2;
	err = TimerConfig(timerConfig);
	
	return (err);
}

DDA_Err_t Timer5Init(void)
{
	DDA_Err_t err = DDA_OK;
	TimerConfig_t timerConfig;
	timerConfig.num = TIMER5;
	timerConfig.mode = TIMER_MODE_PERIOD;
	timerConfig.unit = TIMER_UNIT_MS;
	timerConfig.timeout = 1;
	err = TimerConfig(timerConfig);
	
	return (err);
}

DDA_Err_t Timer6Init(void)
{
	DDA_Err_t err = DDA_OK;
	TimerConfig_t timerConfig;
	timerConfig.num = TIMER6;
	timerConfig.mode = TIMER_MODE_PERIOD;
	timerConfig.unit = TIMER_UNIT_S;
	timerConfig.timeout = 1;
	err = TimerConfig(timerConfig);
	
	return (err);
}

DDA_Err_t Timer7Init(void) // 定时器7的时钟应该不是72M，感觉得有500M
{
	DDA_Err_t err = DDA_OK;
	TimerConfig_t timerConfig;
	timerConfig.num = TIMER7;
	timerConfig.mode = TIMER_MODE_PERIOD;
	timerConfig.unit = TIMER_UNIT_S;
	timerConfig.timeout = 8;
	err = TimerConfig(timerConfig);
	
	return (err);
}

DDA_Err_t TimerInit(void)
{
	DDA_Err_t err = DDA_OK;
	err = Timer2Init();
	err = Timer3Init();
	err = Timer4Init();
	err = Timer5Init();
	err = Timer6Init();
	err = Timer7Init();
	
	return(err);
}

