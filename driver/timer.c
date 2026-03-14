#include "timer.h"

/*
高级控制定时器timer1、timer8
通用定时器timer2、timer3、timer4、timer5
基本定时器timer6、timer7
*/

//时钟为系统时钟72M，即 APB1 的 2 倍，而 APB1 为 36M    Stm32_Clock_Init 函数配置系统时钟
DDA_Err_t TimerConfig(TimerConfig_t timerConfig)
{
	DDA_Err_t err = DDA_OK;
	uint16_t reloadValue; // 重装载值寄存器最大是16位
	uint16_t prescaler; // 预分频器寄存器最大值是16位
	switch (timerConfig.num) {
		case TIMER1: 
			err = DDA_FAIL;
			break;
		case TIMER2: 
			RCC->APB1ENR |= 1<<0; //TIM2 时钟使能 
			TIM2->DIER |= 1<<0; //允许更新中断 
			TIM2->CR1 |= 0x01; //使能定时器 2
			// TIM2->CR1 |= 1<<4; //向下计数方向，默认向上计数
			if (timerConfig.mode == TIMER_MODE_ONCE) { // 默认周期
				TIM2->CR1 |= 1<<3;
			}
		
			switch (timerConfig.unit) {
				case TIMER_UNIT_US: 
					prescaler = 72;
					reloadValue = timerConfig.timeout;
					break;
				case TIMER_UNIT_MS: 
					prescaler = 7200;
					reloadValue = timerConfig.timeout * 10;
					break;
				case TIMER_UNIT_S: 
					prescaler = 7200;
					reloadValue = timerConfig.timeout * 10000;
					break;
				default: break;
			}
			TIM2->ARR = reloadValue; //设定计数器自动重装值//刚好 1ms 
			TIM2->PSC = prescaler; //预分频器 7200,得到 10Khz 的计数时钟 
			
			MY_NVIC_Init(1, 2, TIM2_IRQn, 2);//抢占 1，子优先级 2，组 2
			break;
		case TIMER3: 
			RCC->APB1ENR |= 1<<1; //TIM3 时钟使能 
			TIM3->DIER |= 1<<0; //允许更新中断 
			TIM3->CR1 |= 0x01; //使能定时器 3
			// TIM3->CR1 |= 1<<4; //向下计数方向，默认向上计数
			if (timerConfig.mode == TIMER_MODE_ONCE) { // 默认周期
				TIM3->CR1 |= 1<<3;
			}
		
			switch (timerConfig.unit) {
				case TIMER_UNIT_US: 
					prescaler = 72;
					reloadValue = timerConfig.timeout;
					break;
				case TIMER_UNIT_MS: 
					prescaler = 7200;
					reloadValue = timerConfig.timeout * 10;
					break;
				case TIMER_UNIT_S: 
					prescaler = 7200;
					reloadValue = timerConfig.timeout * 10000;
					break;
				default: break;
			}
			TIM3->ARR = reloadValue; //设定计数器自动重装值//刚好 1ms 
			TIM3->PSC = prescaler; //预分频器 7200,得到 10Khz 的计数时钟 
			
			MY_NVIC_Init(1,3,TIM3_IRQn,2);//抢占 1，子优先级 3，组 2
			break;
		case TIMER4: 
			RCC->APB1ENR |= 1<<2; //TIM4 时钟使能 
			TIM4->DIER |= 1<<0; //允许更新中断 
			TIM4->CR1 |= 0x01; //使能定时器 4
			// TIM2->CR1 |= 1<<4; //向下计数方向，默认向上计数
			if (timerConfig.mode == TIMER_MODE_ONCE) { // 默认周期
				TIM4->CR1 |= 1<<3;
			}
		
			switch (timerConfig.unit) {
				case TIMER_UNIT_US: 
					prescaler = 72;
					reloadValue = timerConfig.timeout;
					break;
				case TIMER_UNIT_MS: 
					prescaler = 7200;
					reloadValue = timerConfig.timeout * 10;
					break;
				case TIMER_UNIT_S: 
					prescaler = 7200;
					reloadValue = timerConfig.timeout * 10000;
					break;
				default: break;
			}
			TIM4->ARR = reloadValue; //设定计数器自动重装值//刚好 1ms 
			TIM4->PSC = prescaler; //预分频器 7200,得到 10Khz 的计数时钟 
			
			MY_NVIC_Init(1, 4, TIM4_IRQn, 2);
			break;
		case TIMER5: 
			RCC->APB1ENR |= 1<<3; //TIM5 时钟使能 
			TIM5->DIER |= 1<<0; //允许更新中断 
			TIM5->CR1 |= 0x01; //使能定时器 5
			// TIM2->CR1 |= 1<<4; //向下计数方向，默认向上计数
			if (timerConfig.mode == TIMER_MODE_ONCE) { // 默认周期
				TIM5->CR1 |= 1<<3;
			}
		
			switch (timerConfig.unit) {
				case TIMER_UNIT_US: 
					prescaler = 72;
					reloadValue = timerConfig.timeout;
					break;
				case TIMER_UNIT_MS: 
					prescaler = 7200;
					reloadValue = timerConfig.timeout * 10;
					break;
				case TIMER_UNIT_S: 
					prescaler = 7200;
					reloadValue = timerConfig.timeout * 10000;
					break;
				default: break;
			}
			TIM5->ARR = reloadValue; //设定计数器自动重装值//刚好 1ms 
			TIM5->PSC = prescaler; //预分频器 7200,得到 10Khz 的计数时钟 
			
			MY_NVIC_Init(1, 5, TIM5_IRQn, 2);
			break;
		case TIMER6: 
			RCC->APB1ENR |= 1<<4; //TIM6 时钟使能 
			TIM6->DIER |= 1<<0; //允许更新中断 
			TIM6->CR1 |= 0x01; //使能定时器 6
			// TIM2->CR1 |= 1<<4; //向下计数方向，默认向上计数
			if (timerConfig.mode == TIMER_MODE_ONCE) { // 默认周期
				TIM6->CR1 |= 1<<3;
			}
		
			switch (timerConfig.unit) {
				case TIMER_UNIT_US: 
					prescaler = 72;
					reloadValue = timerConfig.timeout;
					break;
				case TIMER_UNIT_MS: 
					prescaler = 7200;
					reloadValue = timerConfig.timeout * 10;
					break;
				case TIMER_UNIT_S: 
					prescaler = 7200;
					reloadValue = timerConfig.timeout * 10000;
					break;
				default: break;
			}
			TIM6->ARR = reloadValue;
			TIM6->PSC = prescaler;
			
			MY_NVIC_Init(1, 6, TIM6_IRQn, 2);
			break;
		case TIMER7: 
			RCC->APB1ENR |= 1<<5; //TIM7 时钟使能 
			TIM7->DIER |= 1<<0; //允许更新中断 
			TIM7->CR1 |= 0x01; //使能定时器 7
			// TIM2->CR1 |= 1<<4; //向下计数方向，默认向上计数
			if (timerConfig.mode == TIMER_MODE_ONCE) { // 默认周期
				TIM7->CR1 |= 1<<3;
			}
		
			switch (timerConfig.unit) {
				case TIMER_UNIT_US: 
					prescaler = 72;
					reloadValue = timerConfig.timeout;
					break;
				case TIMER_UNIT_MS: 
					prescaler = 7200;
					reloadValue = timerConfig.timeout * 10;
					break;
				case TIMER_UNIT_S: 
					prescaler = 7200;
					reloadValue = timerConfig.timeout * 10000;
					break;
				default: break;
			}
			TIM7->ARR = reloadValue;
			TIM7->PSC = prescaler;
			
			MY_NVIC_Init(1, 7, TIM7_IRQn, 2);
			break;
		case TIMER8: 
			err = DDA_FAIL;
			break;
		default: 
			err = DDA_EXCEED;
			break;
	}
	
	return (err);
}

uint32_t timer2num = 0;
void TIM2_IRQHandler(void)
{ 
	if(TIM2->SR&0X0001) //溢出中断
	{
		timer2num++;
	} 
	TIM2->SR &= ~(1<<0); //清除中断标志位 
}

uint32_t timer3num = 0;
void TIM3_IRQHandler(void)
{ 
	if(TIM3->SR&0X0001) //溢出中断
	{
		timer3num++;
	} 
	TIM3->SR &= ~(1<<0); //清除中断标志位 
}

uint32_t timer4num = 0;
void TIM4_IRQHandler(void)
{ 
	if(TIM4->SR&0X0001) //溢出中断
	{
		timer4num++;
	} 
	TIM4->SR &= ~(1<<0); //清除中断标志位 
}


uint32_t g_tick = 0;
void (*g_callback)(void *) = NULL;
void TIM5_IRQHandler(void)
{ 
	if(TIM5->SR&0X0001) //溢出中断
	{
		g_tick++;
		(*g_callback)(0); // 调度检查
	} 

	TIM5->SR &= ~(1<<0); //清除中断标志位 
}

uint32_t GetTick(void)
{
	return (g_tick);
}

uint32_t timer6num = 0;
void TIM6_IRQHandler(void)
{ 
	if(TIM6->SR&0X0001) //溢出中断
	{
		timer6num++;
	} 
	TIM6->SR &= ~(1<<0); //清除中断标志位 
}

uint32_t timer7num = 0;
void TIM7_IRQHandler(void)
{ 
	if(TIM7->SR&0X0001) //溢出中断
	{
		timer7num++;
	} 
	TIM7->SR &= ~(1<<0); //清除中断标志位 
}

