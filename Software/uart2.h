#ifndef __UART2_H__
#define __UART2_H__

#define S2RI 0x01	//串口2接收中断请求标志位
#define S2TI 0x02	//串口2发送中断请求标志位

void Uart_Init_2(void);
void UART_2SendOneByte(unsigned char c);
void Send_String_2(unsigned char *str);






#endif