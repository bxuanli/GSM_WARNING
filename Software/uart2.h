#ifndef __UART2_H__
#define __UART2_H__

#define S2RI 0x01	//����2�����ж������־λ
#define S2TI 0x02	//����2�����ж������־λ

void Uart_Init_2(void);
void UART_2SendOneByte(unsigned char c);
void Send_String_2(unsigned char *str);






#endif