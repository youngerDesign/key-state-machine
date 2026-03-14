#ifndef APP_SOFT_TIMER_H
#define APP_SOFT_TIMER_H

#include "app_timer.h"

typedef enum DDA_TimerState {
	TIMER_STATE_CLOSE,
	TIMER_STATE_OPEN,
} DDA_TimerState_t;

typedef struct DDA_Timer {
	uint32_t timerTick;
	uint32_t timeout;
	void (*callback)(void *);
	uint8_t isPeriod;
	DDA_TimerState_t timerState;
	struct DDA_Timer *next;
	struct DDA_Timer *last;
} DDA_Timer_t;

extern DDA_Timer_t g_timerHead;

extern DDA_Err_t SoftTimerInit(void);
extern DDA_Timer_t* DDA_TimerCreate(void (*callback)(void), uint8_t isPeriod, uint32_t timeout);
extern DDA_Err_t DDA_TimerDestroy(DDA_Timer_t *timer);
extern DDA_Err_t DDA_TimerStart(DDA_Timer_t *timer);
extern DDA_Err_t DDA_TimerEnd(DDA_Timer_t *timer);
#endif
