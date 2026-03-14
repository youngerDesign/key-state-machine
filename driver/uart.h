#ifndef UART_H__
#define UART_H__

#include "sys.h"
#include "dda_kernel.h"

#define UART2_RECV_MAX_LEN  			200  	//定义最大接收字节数 200
#define UART3_RECV_MAX_LEN  			200  	//定义最大接收字节数 200
#define UART4_RECV_MAX_LEN  			200  	//定义最大接收字节数 200
#define UART5_RECV_MAX_LEN  			200  	//定义最大接收字节数 200

typedef enum UartNum {
	UART_NUM1 = 1,
	UART_NUM2,
	UART_NUM3,
	UART_NUM4,
	UART_NUM5,
} UartNum_t;

typedef struct UartConfig {
	UartNum_t uartNum;
	uint16_t baudRate;
	uint8_t stopBit;
	uint8_t checkBit;
} UartConfig_t;

extern void UartConfig(UartConfig_t uartConfig);
extern void Uart2Send(char *data, uint8_t len);
extern void Uart3Send(char *data, uint8_t len);
extern void Uart4Send(char *data, uint8_t len);
extern void Uart5Send(char *data, uint8_t len);

extern u8 uart2RecvData[UART2_RECV_MAX_LEN];
extern u8 uart3RecvData[UART3_RECV_MAX_LEN];
extern u8 uart4RecvData[UART4_RECV_MAX_LEN];
extern u8 uart5RecvData[UART5_RECV_MAX_LEN];
extern uint8_t recvCompleteInteruptFlag;

#endif
