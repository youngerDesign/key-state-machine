#ifndef TIMER_H__
#define TIMER_H__

#include "sys.h"
#include "dda_kernel.h"

typedef enum TimerNum {
	TIMER1 = 1,
	TIMER2,
	TIMER3,
	TIMER4,
	TIMER5,
	TIMER6,
	TIMER7,
	TIMER8,
} TimerNum_t;

typedef enum TimerUnit {
	TIMER_UNIT_US,
	TIMER_UNIT_MS,
	TIMER_UNIT_S,	
} TimerUnit_t;

typedef enum TimerMode {
	TIMER_MODE_PERIOD,
	TIMER_MODE_ONCE,
} TimerMode_t;

typedef struct TimerConfig {
	TimerNum_t num;
	TimerMode_t mode;
	TimerUnit_t unit;
	uint16_t timeout;
} TimerConfig_t;

extern DDA_Err_t TimerConfig(TimerConfig_t timerConfig);
extern uint32_t GetTick(void);

extern uint32_t timer2num;
extern uint32_t timer3num;
extern uint32_t timer4num;
//extern uint32_t g_tick;
extern uint32_t timer6num;
extern uint32_t timer7num;

extern void (*g_callback)(void *);
#endif
