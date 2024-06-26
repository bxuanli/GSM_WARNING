 #include <12C5A60S2.h>
 #include "uart2.h"
 	
 void Uart_Init_2 (void)
 {
    
	S2CON = 0x50;   //串口2工作在方式1  10位异步收发 S2REN=1允许接收
    BRT = 0xFd;	    //独立波特率发生器初值 9600
    AUXR = 0x10;    //BRTR=1 独立波特率发生器开始计数
    IE2 =0x01;	    //开串口2中断  ES2=1
 }
 /****************串行口2发送****************/	  
void UART_2SendOneByte(unsigned char c)
{
    S2BUF = c;
    while(!(S2CON&S2TI));  //若S2TI=0，在此等待
    S2CON&=~S2TI;	  //S2TI=0
}
/********串口2字符串发送函数***********/
void Send_String_2(unsigned char *str)		
{
	while(*str != '\0')		
	{
		UART_2SendOneByte(*str);			
		*str=*str++;		
	}
	*str = 0;				  
}