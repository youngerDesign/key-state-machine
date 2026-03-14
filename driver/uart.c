#include "uart.h"
#include "usart.h"


void UartConfig(UartConfig_t uartConfig)
{
	switch (uartConfig.uartNum) {
		case UART_NUM1: break;
		case UART_NUM2: 
			RCC->APB1ENR |= 1<<17; //使能串口2时钟
		
			RCC->APB1RSTR |= 1<<17; //复位串口2
			RCC->APB1RSTR &= ~(1<<17);//停止复位 

			USART2->BRR = uartConfig.baudRate; //波特率设置，可以理解为分频器，串口时钟是36M，36M/BRR=波特率
	
			USART2->CR1 |= 0X200C; //1 位停止,无校验位
			
			USART2->CR1 |= 1<<5; //使能接收中断
			USART2->CR1 |= 1<<4; // 使能idle中断 
		
			MY_NVIC_Init(1,0,USART2_IRQn,2); //抢占优先级1，响应优先级0，组2
			break;
		case UART_NUM3: 
			RCC->APB1ENR |= 1<<18; //使能串口3时钟
		
			RCC->APB1RSTR |= 1<<18; //复位串口3
			RCC->APB1RSTR &= ~(1<<18); //停止复位 

			USART3->BRR = uartConfig.baudRate; // 波特率设置，可以理解为分频器，串口时钟是36M，36M/BRR=波特率
	
			USART3->CR1 |= 0X200C; //1 位停止,无校验位
			
			USART3->CR1 |= 1<<5; //使能接收中断
			USART3->CR1 |= 1<<4; // 使能idle中断 
		
			MY_NVIC_Init(1,0,USART3_IRQn,2); //抢占优先级1，响应优先级0，组2
			break;
		case UART_NUM4: 
			RCC->APB1ENR |= 1<<19; //使能串口3时钟
		
			RCC->APB1RSTR |= 1<<19; //复位串口3
			RCC->APB1RSTR &= ~(1<<19); //停止复位 

			UART4->BRR = uartConfig.baudRate; // 波特率设置，可以理解为分频器，串口时钟是36M，36M/BRR=波特率
	
			UART4->CR1 |= 0X200C; //1 位停止,无校验位
			
			UART4->CR1 |= 1<<5; //使能接收中断
			UART4->CR1 |= 1<<4; // 使能idle中断 
		
			MY_NVIC_Init(1,0,UART4_IRQn,2); //抢占优先级1，响应优先级0，组2
			break;
		case UART_NUM5: 
			RCC->APB1ENR |= 1<<20; //使能串口3时钟
		
			RCC->APB1RSTR |= 1<<20; //复位串口3
			RCC->APB1RSTR &= ~(1<<20); //停止复位 

			UART5->BRR = uartConfig.baudRate; // 波特率设置，可以理解为分频器，串口时钟是36M，36M/BRR=波特率
	
			UART5->CR1 |= 0X200C; //1 位停止,无校验位
			
			UART5->CR1 |= 1<<5; //使能接收中断
			UART5->CR1 |= 1<<4; // 使能idle中断 
		
			MY_NVIC_Init(1,0,UART5_IRQn,2); //抢占优先级1，响应优先级0，组2
			break;
		default: break;
	}
}

uint8_t uart2RecvData[UART2_RECV_MAX_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u16 uart2RecvIndex = 0; 
uint8_t recvCompleteInteruptFlag = 0;

void USART2_IRQHandler(void)                    //串口2中断服务程序
{
    u8 res;	
	if(USART2->SR&(1<<5))	//接收到数据
	{	
		//printf("uart2 USART2_IRQHandler\r\n"); //中断回调里不能加日志，影响中断效率，导致丢包
		uart2RecvData[uart2RecvIndex++] = USART2->DR;  // 读取后自动清中断
		if (uart2RecvIndex > UART2_RECV_MAX_LEN) {
			uart2RecvIndex = 0;
		}							     
	} else if(USART2->SR&(1<<4)) { // idle中断
		recvCompleteInteruptFlag = 2;
		uart2RecvIndex = 0;
		res = USART2->SR;
		res = USART2->DR;  // 读取这两个寄存器是为了清除idle中断
	}
}

void Uart2Send(char *data, uint8_t len)
{
	int i = 0;
	for(i = 0; i < len; i++)
	{
		USART2->DR = data[i];
		while((USART2->SR & 0X40) == 0); //等待发送结束
	}
}


uint8_t uart3RecvData[UART3_RECV_MAX_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u16 uart3RecvIndex = 0; 

void USART3_IRQHandler(void)                    //串口2中断服务程序
{
    u8 res;	
	if(USART3->SR&(1<<5))	//接收到数据
	{	
		//printf("uart3 recieve data\r\n"); //中断回调里不能加日志，影响中断效率，导致丢包
		uart3RecvData[uart3RecvIndex++] = USART3->DR;  // 读取后自动清中断
		if (uart3RecvIndex > UART3_RECV_MAX_LEN) {
			uart3RecvIndex = 0;
		}							     
	} else if(USART3->SR&(1<<4)) { // idle中断
		recvCompleteInteruptFlag = 3;
		uart3RecvIndex = 0;
		res = USART3->SR;
		res = USART3->DR;  // 读取这两个寄存器是为了清除idle中断
		//printf("uart3 recv completed\r\n");
	}
	//printf("uart3 USART3_IRQHandler\r\n");
}

void Uart3Send(char *data, uint8_t len)
{
	int i = 0;
	for(i = 0; i < len; i++)
	{
		USART3->DR = data[i];
		while((USART3->SR & 0X40) == 0); //等待发送结束
	}
}


uint8_t uart4RecvData[UART4_RECV_MAX_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u16 uart4RecvIndex = 0; 

void UART4_IRQHandler(void)                    //串口2中断服务程序
{
    u8 res;	
	if(UART4->SR&(1<<5))	//接收到数据
	{	
		//printf("uart4 recieve data\r\n"); //中断回调里不能加日志，影响中断效率，导致丢包
		uart4RecvData[uart4RecvIndex++] = UART4->DR;  // 读取后自动清中断
		if (uart4RecvIndex > UART4_RECV_MAX_LEN) {
			uart4RecvIndex = 0;
		}							     
	} else if(UART4->SR&(1<<4)) { // idle中断
		recvCompleteInteruptFlag = 4;
		uart4RecvIndex = 0;
		res = UART4->SR;
		res = UART4->DR;  // 读取这两个寄存器是为了清除idle中断
		//printf("uart4 recv completed\r\n");
	}
	//printf("uart4 USART4_IRQHandler\r\n");
}

void Uart4Send(char *data, uint8_t len)
{
	int i = 0;
	for(i = 0; i < len; i++)
	{
		UART4->DR = data[i];
		while((UART4->SR & 0X40) == 0); //等待发送结束
	}
}


uint8_t uart5RecvData[UART5_RECV_MAX_LEN];     //接收缓冲,最大USART_REC_LEN个字节.
u16 uart5RecvIndex = 0; 

void UART5_IRQHandler(void)                    //串口2中断服务程序
{
    u8 res;	
	if(UART5->SR&(1<<5))	//接收到数据
	{	
		//printf("uart4 recieve data\r\n"); //中断回调里不能加日志，影响中断效率，导致丢包
		uart5RecvData[uart5RecvIndex++] = UART5->DR;  // 读取后自动清中断
		if (uart5RecvIndex > UART4_RECV_MAX_LEN) {
			uart5RecvIndex = 0;
		}							     
	} else if(UART5->SR&(1<<4)) { // idle中断
		recvCompleteInteruptFlag = 5;
		uart5RecvIndex = 0;
		res = UART5->SR;
		res = UART5->DR;  // 读取这两个寄存器是为了清除idle中断
		//printf("uart4 recv completed\r\n");
	}
	//printf("uart4 USART4_IRQHandler\r\n");
}

void Uart5Send(char *data, uint8_t len)
{
	int i = 0;
	for(i = 0; i < len; i++)
	{
		UART5->DR = data[i];
		while((UART5->SR & 0X40) == 0); //等待发送结束
	}
}
