 #include <12C5A60S2.h>
 #include "uart2.h"
 	
 void Uart_Init_2 (void)
 {
    
	S2CON = 0x50;   //����2�����ڷ�ʽ1  10λ�첽�շ� S2REN=1�������
    BRT = 0xFd;	    //���������ʷ�������ֵ 9600
    AUXR = 0x10;    //BRTR=1 ���������ʷ�������ʼ����
    IE2 =0x01;	    //������2�ж�  ES2=1
 }
 /****************���п�2����****************/	  
void UART_2SendOneByte(unsigned char c)
{
    S2BUF = c;
    while(!(S2CON&S2TI));  //��S2TI=0���ڴ˵ȴ�
    S2CON&=~S2TI;	  //S2TI=0
}
/********����2�ַ������ͺ���***********/
void Send_String_2(unsigned char *str)		
{
	while(*str != '\0')		
	{
		UART_2SendOneByte(*str);			
		*str=*str++;		
	}
	*str = 0;				  
}