#ifndef APP_KEY_H__
#define APP_KEY_H__


#include "gpio.h"

#define KEY0 PEin(4) //PE4
#define KEY1 PEin(3) //PE3 
#define KEY2 PEin(2) //PE2
#define WK_UP PAin(0) //PA0 WK_UP 即 KEY_UP

#define KEY0_PRES 1 //KEY0 按下
#define KEY1_PRES 2 //KEY1 按下
#define KEY2_PRES 3 //KEY2 按下
#define WKUP_PRES 4 //KEY_UP 按下(即 WK_UP/KEY_UP)

extern DDA_Err_t KeyInit(void);
extern DDA_Err_t KeyExtiInit(void);
extern u8 KEY_Scan(u8 mode);

extern DDA_Err_t Key0ExtiInit(void);
extern uint8_t KeyLevelRead(void);

#endif
