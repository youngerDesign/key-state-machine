#ifndef APP_KEY_STATE_MACHINE_H__
#define APP_KEY_STATE_MACHINE_H__

#include "sys.h"
#include "dda_kernel.h"

extern uint8_t g_keyMessageQueue;

extern DDA_Err_t KeyStateMachineInit(void);
extern DDA_Err_t APP_KeyThreadEntry(void);

#endif
