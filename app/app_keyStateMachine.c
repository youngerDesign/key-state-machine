/*
按键状态机，支持单次、连击、长按
四种状态：释放、单次按下、长按、连击
添加一个周期性定时器
捋思路的时候按照正常的 按下-》单次-》长按 顺序来捋就行了，每一种状态都会面临两种中断输入（按键、超时），对应切换不同的状态
支持连击时长按，最后输出长按和连击数
长按支持3s一个8s一个，时间可以累积
需要在中断那里防抖
连击条件：150ms内松开并点击第二下才算
长按条件：长按超过300ms识别为长按
*/
#include "app_keyStateMachine.h"
#include "app_key.h"
#include "app_softTimer.h"
#include "usart.h"

#define KEY_RELEASE_LEVEL 0

typedef enum KeyState {
	KEY_STATE_RELEASE,
	KEY_STATE_SHORT_PRESS,
	KEY_STATE_LONG_PRESS,
	KEY_STATE_REPEAT,
} KeyState_t;

uint8_t g_keyMessageQueue = 0; // 模拟按键给其他线程发消息

typedef struct KeyHandle {
	KeyState_t keyState;
	uint32_t lastTick;
	DDA_Timer_t *timer;
	uint32_t pressTime;
	uint8_t repeatNum;
} KeyHandle_t;

KeyHandle_t g_keyHandle;

typedef enum KeyValue {
	KEY_VALUE_NONE,
	KEY_VSLUE_LONG_PRESS_3S = 20,
	KEY_VSLUE_LONG_PRESS_8S = 21,
} KeyValue_t;

DDA_Err_t APP_KeyTimerCallback(void)
{
	g_keySemaphore++;
	return DDA_OK;
}

DDA_Err_t KeyStateMachineInit(void)
{
	KeyExtiInit();
	g_keyHandle.timer = DDA_TimerCreate(APP_KeyTimerCallback, 1, 150);
}

DDA_Err_t KeyStateMachine(uint32_t interval)
{
	uint8_t keyLevel = KeyLevelRead();
	switch (g_keyHandle.keyState) {
		case KEY_STATE_RELEASE: 
			if (keyLevel == KEY_RELEASE_LEVEL) { // timeout
				g_keyMessageQueue = g_keyHandle.repeatNum; // 连续按下超时，输出重复次数
				DDA_TimerEnd(g_keyHandle.timer);
				g_keyHandle.pressTime = 0; // 按下时间清零
				g_keyHandle.repeatNum = 0; // 重复次数清零
			} else { // 按下中断
				if (g_keyHandle.repeatNum != 0) {
					g_keyHandle.keyState = KEY_STATE_REPEAT;
				} else {
					g_keyHandle.keyState = KEY_STATE_SHORT_PRESS;
				}
				g_keyHandle.repeatNum++;
				DDA_TimerEnd(g_keyHandle.timer);
				DDA_TimerStart(g_keyHandle.timer);
			}
			break;
		case KEY_STATE_SHORT_PRESS: 
			if (keyLevel == KEY_RELEASE_LEVEL) { // 松开中断
				g_keyHandle.keyState = KEY_STATE_RELEASE;
			} else { // timeout
				g_keyHandle.pressTime += interval;
				if (g_keyHandle.pressTime > 300) {
					g_keyHandle.keyState = KEY_STATE_LONG_PRESS;
				}
			}
			break;
		case KEY_STATE_LONG_PRESS: 
			if (keyLevel == KEY_RELEASE_LEVEL) { // 松开中断
				g_keyHandle.keyState = KEY_STATE_RELEASE;
			} else { // timeout
				g_keyHandle.pressTime += interval;
				if (g_keyHandle.pressTime > 2930 && g_keyHandle.pressTime < 3080) { // 3s左右150ms
					g_keyMessageQueue = KEY_VSLUE_LONG_PRESS_3S; // 表示长按3s
				} else if (g_keyHandle.pressTime > 7930 && g_keyHandle.pressTime < 8080) { // 8s左右150ms
					g_keyMessageQueue = KEY_VSLUE_LONG_PRESS_8S; // 表示长按8s
				}
			}
			break;
		case KEY_STATE_REPEAT: 
			if (keyLevel == KEY_RELEASE_LEVEL) { // 松开中断
				g_keyHandle.keyState = KEY_STATE_RELEASE;
			} else { // timeout
				g_keyHandle.pressTime += interval;
				if (g_keyHandle.pressTime > 300) {
					g_keyHandle.keyState = KEY_STATE_LONG_PRESS;
				}
			}
			break;
		default:
			// 输出错误日志
			break;
	}
}

DDA_Err_t APP_KeyThreadEntry(void)
{
	if (g_keySemaphore != 0) {
		g_keySemaphore--;
		uint32_t curTick = GetTick();
		KeyStateMachine(curTick - g_keyHandle.lastTick);
		g_keyHandle.lastTick = curTick;
	}
}

