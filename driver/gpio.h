#ifndef GPIO_H__
#define GPIO_H__

#include "sys.h"
#include "dda_kernel.h"

#define GPIO_GROUP_ENABLE_OFFSET 2
#define GPIO_CONTRL_BIT_NUM 4   //控制寄存器CRL、CRH 4位控制一个IO口
#define GPIO_MODE_BIT_NUM 2   // 模式那两位需要左移2位


#define GPIO_PIN_LEVEL_HIGH 1
#define GPIO_PIN_LEVEL_LOW 0

#define TRUE 1

#define GPIO_EXTICR_GROUP 4 // EXTICR寄存器一共分4组，EXTICR寄存器可参考STM32中文手册P127
#define GPIO_EXTICR_BIT_NUM 4 // EXTICR寄存器每4位控制一个pin脚

typedef enum GPIO_Group {
	GPIO_GROUPA,
	GPIO_GROUPB,
	GPIO_GROUPC,
	GPIO_GROUPD,
	GPIO_GROUPE,
	GPIO_GROUPF,
	GPIO_GROUPG,
	GPIO_MAX_NUM,
} GPIO_Group_t;

typedef enum GPIO_Pin {
	GPIO_PIN0,
	GPIO_PIN1,
	GPIO_PIN2,
	GPIO_PIN3,
	GPIO_PIN4,
	GPIO_PIN5,
	GPIO_PIN6,
	GPIO_PIN7,
	GPIO_PIN8,
	GPIO_PIN9,
	GPIO_PIN10,
	GPIO_PIN11,
	GPIO_PIN12,
	GPIO_PIN13,
	GPIO_PIN14,
	GPIO_PIN15,
	GPIO_PIN_MAX_NUM,
} GPIO_Pin_t;

typedef enum GPIO_INPUT_Mode {
	GPIO_Mode_ANALOG, //模拟输入
	GPIO_Mode_FLOATING, //浮空输入
	GPIO_Mode_PULL, //上拉或者下拉输入
	GPIO_Mode_RETENTION,
} GPIO_INPUT_Mode_t;
	
typedef enum GPIO_OUTPUT_Mode {
	GPIO_Mode_PUSH_PULL, //推挽输出
	GPIO_Mode_OPEN_LEAK, //开漏输出
	GPIO_Mode_REUSE_PUSH_PULL, //复用推挽输出
	GPIO_Mode_REUSE_LEAK, //复用开漏输出
} GPIO_OUTPUT_Mode_t;	

typedef enum GPIO_DirectionSpeed {
	GPIO_INPUT_MODE, 
	GPIO_OUTPUT_MODE_SPEED10MHZ,
	GPIO_OUTPUT_MODE_SPEED20MHZ,
	GPIO_OUTPUT_MODE_SPEED50MHZ,
} GPIO_DirectionSpeed_t;

typedef struct GPIO_Config {
	GPIO_Group_t group;
	uint16_t pinMask;
	uint8_t mode;
	uint8_t directionSpeed; // 方向和速度
	uint8_t defaultLevel;
} GPIO_Config_t;

typedef enum ExtiTriggerMode {
	RISING_EDGE_TRIGGER,
	FALLING_EDGE_TRIGGER,
	DOUBLE_EDGE_TRIGGER,
} ExtiTriggerMode_t;

typedef struct GPIO_ExtiConfig{
	GPIO_Group_t group;
	uint16_t pinMask;
	ExtiTriggerMode_t triggerMode;
} GPIO_ExtiConfig_t;

extern DDA_Err_t GPIO_ClockEnable(GPIO_Group_t gpioGroup, uint8_t enable);
extern DDA_Err_t GPIO_Config(GPIO_Config_t* config);
extern DDA_Err_t GPIO_PinWritePin(GPIO_Group_t group, GPIO_Pin_t pin, uint8_t level);
extern uint8_t GPIO_PinReadPin(GPIO_Group_t group, GPIO_Pin_t pin);
extern uint16_t GPIO_PinRead(GPIO_Group_t group);
extern DDA_Err_t GPIO_ExtiConfig(GPIO_ExtiConfig_t *extiConfig);

extern uint8_t extiNum;
extern uint8_t key0ExtiFlag;
extern uint8_t g_keySemaphore;
#endif

