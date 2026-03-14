#include "gpio.h"
#include "delay.h"

DDA_Err_t GPIO_ClockEnable(GPIO_Group_t gpioGroup, uint8_t enable) // 只支持串行操作，不支持一次使能多组IO口
{
	if (gpioGroup >= GPIO_MAX_NUM) {
		return (DDA_EXCEED);
	}

	gpioGroup += GPIO_GROUP_ENABLE_OFFSET; // 使能位偏移两个，即寄存器中规定gpioA使能位时第2位
	if (enable == 0) {
		RCC->APB2ENR &= ~(1<<gpioGroup);
	} else {
		RCC->APB2ENR |= 1<<gpioGroup;
	}
	
	return (DDA_OK);
}

DDA_Err_t GPIO_Config(GPIO_Config_t* config) // 支持并脚操作
{
	// 缺少指针判空
	DDA_Err_t err = DDA_OK;
	uint16_t pinMask = config->pinMask;
	uint8_t pin;

	switch (config->group) {
		case GPIO_GROUPA: 
			for (pin = 0; pinMask != 0; pin++) { // 并脚操作
				if ((pinMask & (1<<pin)) != 0) {
					
					if (pin < GPIO_PIN8) {
						GPIOA->CRL &= ~(0xF<<(pin * GPIO_CONTRL_BIT_NUM));
						GPIOA->CRL |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<(pin * GPIO_CONTRL_BIT_NUM); // 配置模式、方向、速度
					} else {
						GPIOA->CRH &= ~(0xF<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM));
						GPIOA->CRH |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM);
					}
					
					if (config->defaultLevel == 0) {
						GPIOA->ODR &= ~(1<<(pin));
					} else {
						GPIOA->ODR |= 1<<(pin);
					}
					pinMask ^= (1<<pin);
				}
			}
			break;
		case GPIO_GROUPB: 
			for (pin = 0; pinMask != 0; pin++) {
				if ((pinMask & (1<<pin)) != 0) {
					if (pin < GPIO_PIN8) {
						GPIOB->CRL &= ~(0xF<<(pin * GPIO_CONTRL_BIT_NUM));
						GPIOB->CRL |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<(pin * GPIO_CONTRL_BIT_NUM); // 配置模式、方向、速度
					} else {
						GPIOB->CRH &= ~(0xF<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM));
						GPIOB->CRH |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM);
					}
					
					if (config->defaultLevel == 0) {
						GPIOB->ODR &= ~(1<<(pin));
					} else {
						GPIOB->ODR |= 1<<(pin);
					}
					pinMask ^= (1<<pin);
				}
			}
			break;
		case GPIO_GROUPC: 
			for (pin = 0; pinMask != 0; pin++) {
				if ((pinMask & (1<<pin)) != 0) {
					if (pin < GPIO_PIN8) {
						GPIOC->CRL &= ~(0xF<<(pin * GPIO_CONTRL_BIT_NUM));
						GPIOC->CRL |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<(pin * GPIO_CONTRL_BIT_NUM); // 配置模式、方向、速度
					} else {
						GPIOC->CRH &= ~(0xF<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM));
						GPIOC->CRH |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM);
					}
					
					if (config->defaultLevel == 0) {
						GPIOC->ODR &= ~(1<<(pin));
					} else {
						GPIOC->ODR |= 1<<(pin);
					}
					pinMask ^= (1<<pin);
				}
			}
			break;
		case GPIO_GROUPD: 
			for (pin = 0; pinMask != 0; pin++) {
				if ((pinMask & (1<<pin)) != 0) {
					if (pin < GPIO_PIN8) {
						GPIOD->CRL &= ~(0xF<<(pin * GPIO_CONTRL_BIT_NUM));
						GPIOD->CRL |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<(pin * GPIO_CONTRL_BIT_NUM); // 配置模式、方向、速度
					} else {
						GPIOD->CRH &= ~(0xF<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM));
						GPIOD->CRH |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM);
					}
					
					if (config->defaultLevel == 0) {
						GPIOD->ODR &= ~(1<<(pin));
					} else {
						GPIOD->ODR |= 1<<(pin);
					}
					pinMask ^= (1<<pin);
				}
			}
			break;
		case GPIO_GROUPE: 
			for (pin = 0; pinMask != 0; pin++) {
				if ((pinMask & (1<<pin)) != 0) {
					if (pin < GPIO_PIN8) {
						GPIOE->CRL &= ~(0xF<<(pin * GPIO_CONTRL_BIT_NUM));
						GPIOE->CRL |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<(pin * GPIO_CONTRL_BIT_NUM); // 配置模式、方向、速度
					} else {
						GPIOE->CRH &= ~(0xF<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM));
						GPIOE->CRH |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM);
					}
					
					if (config->defaultLevel == 0) {
						GPIOE->ODR &= ~(1<<(pin));
					} else {
						GPIOE->ODR |= 1<<(pin);
					}
					pinMask ^= (1<<pin);
				}
			}
			break;
		case GPIO_GROUPF: 
			for (pin = 0; pinMask != 0; pin++) {
				if ((pinMask & (1<<pin)) != 0) {
					if (pin < GPIO_PIN8) {
						GPIOF->CRL &= ~(0xF<<(pin * GPIO_CONTRL_BIT_NUM));
						GPIOF->CRL |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<(pin * GPIO_CONTRL_BIT_NUM); // 配置模式、方向、速度
					} else {
						GPIOF->CRH &= ~(0xF<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM));
						GPIOF->CRH |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM);
					}
					
					if (config->defaultLevel == 0) {
						GPIOF->ODR &= ~(1<<(pin));
					} else {
						GPIOF->ODR |= 1<<(pin);
					}
					pinMask ^= (1<<pin);
				}
			}
			break;
		case GPIO_GROUPG: 
			for (pin = 0; pinMask != 0; pin++) {
				if ((pinMask & (1<<pin)) != 0) {
					if (pin < GPIO_PIN8) {
						GPIOG->CRL &= ~(0xF<<(pin * GPIO_CONTRL_BIT_NUM));
						GPIOG->CRL |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<(pin * GPIO_CONTRL_BIT_NUM); // 配置模式、方向、速度
					} else {
						GPIOG->CRH &= ~(0xF<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM));
						GPIOG->CRH |= ((config->mode << GPIO_MODE_BIT_NUM) | config->directionSpeed)<<((pin - GPIO_PIN8) * GPIO_CONTRL_BIT_NUM);
					}
					
					if (config->defaultLevel == 0) {
						GPIOG->ODR &= ~(1<<(pin));
					} else {
						GPIOG->ODR |= 1<<(pin);
					}
					pinMask ^= (1<<pin);
				}
			}
			break;
		
		default: 
			err = DDA_EXCEED;
			break;
	}
	return err;
}

DDA_Err_t GPIO_PinWritePin(GPIO_Group_t group, GPIO_Pin_t pin, uint8_t level) // 写入单个引脚值
{
	
	DDA_Err_t err = DDA_OK;
	switch (group) {
		case GPIO_GROUPA: 
			if (level == 0) {
				GPIOA->ODR &= ~(1<<(pin));
			} else {
				GPIOA->ODR |= 1<<(pin);
			}
			break;
		case GPIO_GROUPB: 
			if (level == 0) {
				GPIOB->ODR &= ~(1<<(pin));
			} else {
				GPIOB->ODR |= 1<<(pin);
			}
			break;
		case GPIO_GROUPC: 
			if (level == 0) {
				GPIOC->ODR &= ~(1<<(pin));
			} else {
				GPIOC->ODR |= 1<<(pin);
			}
			break;
		case GPIO_GROUPD: 
			if (level == 0) {
				GPIOD->ODR &= ~(1<<(pin));
			} else {
				GPIOD->ODR |= 1<<(pin);
			}
			break;
		case GPIO_GROUPE: 
			if (level == 0) {
				GPIOE->ODR &= ~(1<<(pin));
			} else {
				GPIOE->ODR |= 1<<(pin);
			}
			break;
		case GPIO_GROUPF: 
			if (level == 0) {
				GPIOF->ODR &= ~(1<<(pin));
			} else {
				GPIOF->ODR |= 1<<(pin);
			}
			break;
		case GPIO_GROUPG: 
			if (level == 0) {
				GPIOG->ODR &= ~(1<<(pin));
			} else {
				GPIOG->ODR |= 1<<(pin);
			}
			break;
		default:
			err = DDA_EXCEED;
			break;
	}
	return err;
}

uint8_t GPIO_PinReadPin(GPIO_Group_t group, GPIO_Pin_t pin)
{
	uint16_t gpioInputValue = 0;
	uint8_t gpioPinInputLevel= 0;
	switch (group) {
		case GPIO_GROUPA: 
			gpioInputValue = GPIOA->IDR;
			break;
		case GPIO_GROUPB: 
			gpioInputValue = GPIOB->IDR;
			break;
		case GPIO_GROUPC: 
			gpioInputValue = GPIOC->IDR;
			break;
		case GPIO_GROUPD: 
			gpioInputValue = GPIOD->IDR;
			break;
		case GPIO_GROUPE: 
			gpioInputValue = GPIOE->IDR;
			break;
		case GPIO_GROUPF: 
			gpioInputValue = GPIOF->IDR;
			break;
		case GPIO_GROUPG: 
			gpioInputValue = GPIOG->IDR;
			break;
		default:
			// 打印错误日志
			break;
	}
	gpioPinInputLevel = (gpioInputValue >> pin) & 0x01;
	
	return (gpioPinInputLevel);
}

uint16_t GPIO_PinRead(GPIO_Group_t group)
{
	uint16_t gpioInputValue = 0;
	switch (group) {
		case GPIO_GROUPA: 
			gpioInputValue = GPIOA->IDR;
			break;
		case GPIO_GROUPB: 
			gpioInputValue = GPIOB->IDR;
			break;
		case GPIO_GROUPC: 
			gpioInputValue = GPIOC->IDR;
			break;
		case GPIO_GROUPD: 
			gpioInputValue = GPIOD->IDR;
			break;
		case GPIO_GROUPE: 
			gpioInputValue = GPIOE->IDR;
			break;
		case GPIO_GROUPF: 
			gpioInputValue = GPIOF->IDR;
			break;
		case GPIO_GROUPG: 
			gpioInputValue = GPIOG->IDR;
			break;
		default:
			// 打印错误日志
			break;
	}
	
	return (gpioInputValue);
}

DDA_Err_t GPIO_ExtiConfig(GPIO_ExtiConfig_t *extiConfig) // 支持并脚操作   还有优化点，可以不用指针，这样既不需要在函数里定义那么多的变量了
{
	DDA_Err_t err = DDA_OK;
	uint8_t pin;
	uint8_t extiControlGroup;
	uint8_t extiControlOffset;
	uint8_t gpioGroup;
	uint16_t pinMask = extiConfig->pinMask;

	RCC->APB2ENR |= 0x01; //使能gpio复用时钟	
	
	for (pin = 0; pinMask != 0; pin++) {
		if ((pinMask & (1<<pin)) != 0) {
			extiControlGroup = pin / GPIO_EXTICR_GROUP; // 这是因为EXTICR这个寄存器分了4组，每一组只对应4组pin口的中断，比如EXTICR[0]只对应gpioPin0、gpioPin1、gpioPin2、gpioPin3；具体可参考STM32中文参考手册P127该寄存器组描述
			extiControlOffset = pin % GPIO_EXTICR_BIT_NUM; // 同上
			AFIO->EXTICR[extiControlGroup] &= ~(0x000F<<(extiControlOffset * GPIO_EXTICR_BIT_NUM));
			gpioGroup = extiConfig->group;
			AFIO->EXTICR[extiControlGroup] |= gpioGroup<<(extiControlOffset * GPIO_EXTICR_BIT_NUM);
			
			EXTI->IMR |= 1<<pin; //开启pin线上的中断
			switch (extiConfig->triggerMode) {
				case RISING_EDGE_TRIGGER: 
					EXTI->RTSR |= 1<<pin; //pin线上事件上升降沿触发
					break;
				case FALLING_EDGE_TRIGGER: 
					EXTI->FTSR |= 1<<pin; //pin线上事件下降沿触发
					break;
				case DOUBLE_EDGE_TRIGGER: 
					EXTI->RTSR |= 1<<pin; //pin线上事件上升降沿触发
					EXTI->FTSR |= 1<<pin; //pin线上事件下降沿触发
					break;
				default: err = DDA_EXCEED;
					break;
			}
			pinMask ^= (1<<pin);
		}
	}

	return err;
}		

uint8_t extiNum = 0;
uint8_t g_keySemaphore = 0;
void EXTI0_IRQHandler(void)
{
	delay_ms(30);	//消抖
	extiNum++;
	EXTI->PR=1<<0;  //清除LINE0上的中断标志位  
	g_keySemaphore++; // 释放信号量
}

void EXTI2_IRQHandler(void)
{
	delay_ms(10);	//消抖
	extiNum++;
	EXTI->PR=1<<2;  //清除LINE0上的中断标志位  
}

void EXTI3_IRQHandler(void)
{
	delay_ms(10);	//消抖
	extiNum++;
	EXTI->PR=1<<3;  //清除LINE0上的中断标志位  
}

uint8_t key0ExtiFlag = 0;
void EXTI4_IRQHandler(void)
{
	delay_ms(10);	//消抖
	if (GPIO_PinReadPin(GPIO_GROUPE, GPIO_PIN4) == 0) { // 结合上面延时一起消抖
		key0ExtiFlag++;  
	}

	EXTI->PR=1<<4;  //清除LINE0上的中断标志位
}



