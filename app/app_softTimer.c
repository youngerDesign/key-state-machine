#include "app_softTimer.h"
#include "usart.h"

DDA_Timer_t g_timerHead;

DDA_Err_t SchedulCheck(void);


DDA_Err_t SoftTimerInit(void)
{
	Timer5Init(); // 系统tick

	g_callback = SchedulCheck; // 注册调度检查函数，每个tick来临都会检查一下定时器是否超时

	g_timerHead.next = &g_timerHead;
	g_timerHead.last = &g_timerHead;
	return (DDA_OK);
}

DDA_Timer_t* DDA_TimerCreate(void (*callback)(void), uint8_t isPeriod, uint32_t timeout)
{
	DDA_Timer_t *timerNode = (DDA_Timer_t*)malloc(sizeof(DDA_Timer_t));
	timerNode->timeout = timeout;
	timerNode->isPeriod = isPeriod;
	timerNode->callback = callback;
	timerNode->timerState = TIMER_STATE_CLOSE;
	return (timerNode);
}

DDA_Err_t DDA_TimerDestroy(DDA_Timer_t *timer)
{
	free(timer);
	return (DDA_OK);
}

DDA_Err_t DDA_TimerInsert(DDA_Timer_t *head, DDA_Timer_t *node)
{
	DDA_Timer_t *iter = head->next;
	if (iter == head) { // 定时器链表为空
		head->next = node;
		head->last = node;
		node->next = head;
		node->last = head;
		return (DDA_OK);
	}

	//printf("firstTick:%d timerTick:%d   sysTick:%d\r\n", iter->timerTick, node->timerTick, GetTick());
	while (iter != head) { // 新定时器按大小插入
		//printf("last:%d timerTick:%d   sysTick:%d\r\n", iter->timerTick, node->timerTick, GetTick());
		if (iter->timerTick <= node->timerTick) {
			iter = iter->next;
		} else {
			break;
		}
	}

	if (iter != head) { // 新定时器插在链表中间，头插
		//printf("33333   node->timeout:%d\r\n", node->timerTick);
		iter->last->next = node;
		node->next = iter;
		node->last =iter->last;
		iter->last = node;
	} else { // 新定时器插在链表尾
		//printf("44444   node->timeout:%d\r\n", node->timerTick);
		head->last->next = node;
		node->next = head;
		node->last = head->last;
		head->last = node;
	}
	return (DDA_OK);
}

DDA_Err_t DDA_TimerDelete(DDA_Timer_t *node)
{

	if (node == NULL)
	{
		return(DDA_NULL);
	}
	node->last->next = node->next;
	node->next->last = node->last;
	
	return (DDA_OK);
}

DDA_Err_t DDA_TimerStart(DDA_Timer_t *timer)
{
	if (timer->timerState == TIMER_STATE_OPEN) {
		return (DDA_REPEAT);
	}
	timer->timerTick = GetTick() + timer->timeout;
	timer->timerState = TIMER_STATE_OPEN;
	DDA_TimerInsert(&g_timerHead, timer);
	return (DDA_OK);
}

DDA_Err_t DDA_TimerEnd(DDA_Timer_t *timer)
{
	if (timer->timerState == TIMER_STATE_CLOSE) {
		return (DDA_REPEAT);
	}
	DDA_TimerDelete(timer);
	timer->timerState = TIMER_STATE_CLOSE;
	return (DDA_OK);
}

uint8_t g_timerThreadSemaphore = 0;
DDA_Err_t SchedulCheck(void)
{
	if (g_timerHead.next == NULL) {
		return DDA_OK;
	}
	if (GetTick() >= g_timerHead.next->timerTick) {
		g_timerHead.next->callback(NULL);
		DDA_Timer_t *iter = g_timerHead.next;
		DDA_TimerEnd(iter);
		if (iter->isPeriod == 1) {
			DDA_TimerStart(iter);
		}
	}
	return DDA_OK;
}

