#include<12C5A60S2.h>
#include<intrins.h>
#include<ADC.h>
#include "uart2.h"	
#include "sim800.h"	
/********��ȩ���ڽ������ݻ���**********/
unsigned char idata ZE08_receive[30];
/********��ȩ���ڽ��ռ�����**********/
unsigned char  ZE08_DATA_count; 
bit kg_flag = 0;
unsigned char str_ze08[5];//��ȩֵ
unsigned char str_co[5];//ֵ
unsigned char P_baojing = 100;	//��ȩ����ֵ
unsigned int  C_baojing = 100;
unsigned char P_buff[4];
unsigned char C_buff[4];
unsigned char moshi=0;
unsigned char time;
int ZE08,Value1,Value2;
 //unsigned char dat = 0x00;      //ADֵ
bit qx_flag = 1;      //�������� Ĭ�Ͽ�
bit flag_1s ;      //�������� Ĭ�Ͽ�
sbit  shezhi = P3^7;
sbit  jia    = P3^6;
sbit  jian   = P3^5;
sbit  quxiao = P3^4;
sbit  BUZZER = P3^2;
sbit  LED_P  = P1^4;//   ��ȩ����ָʾ��
sbit  LED_C  = P1^5;//  ������ָʾ��
sbit  HW  = P1^6;//  �����Ӧ
unsigned int sum=0;
unsigned char IntToString(unsigned char *str, int dat);
extern void InitLcd1602();
extern void LcdShowStr(unsigned char x, unsigned char y, unsigned char *str);
extern void LcdWriteCmd(unsigned char cmd);
unsigned char *content1 =  "Warning: Vehicle anomaly!\r\n";

void Key_set_scan()
{
  	if(quxiao==0)
	{
	   Delay_Ms(10);

		if(quxiao==0)
		{
		   while(!quxiao);
		  qx_flag =~ qx_flag;
		}
	}  
	if(shezhi==0)
	{
	   Delay_Ms(10);
		if(shezhi==0)
		{  
		   while(!shezhi);
		   LcdWriteCmd(0x01);  //����
		   moshi++;
		   if(moshi >= 3)moshi = 0;
		   if(moshi == 0)
		   { 
              LcdShowStr(0, 0,"HCHO:   ppm T:  ");
              LcdShowStr(0, 1,"Smoke:    ppm");
		   }
		
		   else if(moshi == 1)
		   {    LcdWriteCmd(0x01);  //����
		        Delay_Ms(10);
		       LcdShowStr(0, 0,"                ");
		   	   LcdShowStr(0, 1,"Set_H:    ppm   ");
		   }
		   else if(moshi == 2)
		   {   LcdWriteCmd(0x01);  //����
		       Delay_Ms(10);
		       LcdShowStr(0, 0,"                ");
		   	   LcdShowStr(0, 1,"Set_S:    ppm   ");
		   }		   		   	
		}
	}
	
	if(jia==0)
	{
	   Delay_Ms(80);
		if(jia==0)
		{ 				
			if(moshi==1)
			{
			 P_baojing++ ;
			 if( P_baojing>=999 )P_baojing =999;
			}

			if(moshi==2)
			{
			 C_baojing++ ;
			 if( C_baojing>=999 )C_baojing =999;
			}		
		 }
	 }
	 if(jian == 0)
	 {
	    Delay_Ms(80);
	   if(jian == 0)
	   {
	       
			if(moshi==1)
			{
			 P_baojing-- ;
			 if( P_baojing<=0 )P_baojing =0;
			}
			if(moshi==2)
			{
			 C_baojing-- ;
			 if( C_baojing<=0 )C_baojing =0;
			}
	   }
	 }
		 
}

/*------------------------------------------------
                    ��ʱ����ʼ���ӳ���
------------------------------------------------*/
void Init_Timer0(void)
{
 TMOD |= 0x01;	  //ʹ��ģʽ1��16λ��ʱ����ʹ��"|"���ſ�����ʹ�ö����ʱ��ʱ����Ӱ��		     
 TH0=(65536-5000)/256;		  //���¸�ֵ5ms
 TL0=(65536-5000)%256;
 EA=1;            //���жϴ�
 ET0=1;           //��ʱ���жϴ�
 TR0=1;           //��ʱ�����ش�
 PT0=1;           //���ȼ���
}
/************������****************/
void main()
{  	  
   char len,a,i;
   char buff[3];
//   U8 m;
  InitLcd1602();     //��ʼ��Һ��
  LcdShowStr(0,0,"  System init   ");
  LcdShowStr(0,1,"  please wait   ");
  for(i = 0;i < 15;i++)//�ȴ������ȶ�
 {
		Delay_Ms(1000);
  }
   InitLcd1602();   
  LcdShowStr(0, 0,"HCHO:   ppm T:  ");
  LcdShowStr(0, 1,"Smoke:   ppm    ");

  Init_Timer0();	//��ʱ����ʼ��
  Uart_Init();   //���ò�����Ϊ9600
  Uart_Init_2(); 
  ADC_Init(ADC_PORT0);
 
  while(1)
 {
   
 Key_set_scan();//����ɨ��
 if(moshi == 0)	  //����ģʽ�л�
 {  
    len = IntToString(str_ze08,ZE08); //ת�����ַ���
    while (len < 3)                  //�ÿո��뵽5���ַ�����
    {
        str_ze08[len++] = ' ';
    }
    str_ze08[len] = '\0';              //����ַ���������
    LcdShowStr(5, 0, str_ze08); //��ȩ��ʾ��Һ������ 
	  	 
	Value2 = GetADCResult(ADC_CH0);	  //yanwu ���
    Value2 =  (float)(Value2/2);//Ũ��У׼
    len = IntToString(str_co,Value2); //ת�����ַ���
    while (len < 3)               //�ÿո��뵽3���ַ�����
    {
        str_co[len++] = ' ';
    }
     str_co[len] = '\0';              //����ַ���������
 
   LcdShowStr(6, 1, str_co); //����Ũ����ʾ��Һ������  
   if(qx_flag == 1)
   {
   if((ZE08>=P_baojing)||(Value2>=C_baojing)) BUZZER = 0; else BUZZER = 1;
   }
   else BUZZER = 1;
 
   if(ZE08>=P_baojing)      LED_P = 0;   else  LED_P = 1;	
   if(Value2>=C_baojing)     LED_C = 0;   else  LED_C = 1;

    if(HW==0)
	{	
	  if(flag_1s==1)
	  {
	   flag_1s=0;
	   time++; if(time>99) time=99;
	   buff[0]=time/10+0x30;
	   buff[1]=time%10+0x30;
	   buff[2]=	'\0';
	   LcdShowStr(14, 0,buff);
	   if(time>=5)
	   {
	   	  if(a==0)
		  {  
		   a=1;
		   Send_message(content1);	  //����������
		   //time=0;		   
		  }
	   }
	  }
	}
	else 
	{
	   time=0;
	   buff[0]=time/10+0x30;
	   buff[1]=time%10+0x30;
	   buff[2]=	'\0';
	   LcdShowStr(14, 0,buff);
	}
   	
  }

   else if(moshi == 1)	 //���ü�ȩŨ������ģʽ
   {
   P_buff[0] = P_baojing/100+0x30;
   P_buff[1] = P_baojing%100/10+0x30;
   P_buff[2] = P_baojing%10+0x30;
   P_buff[4] = '\0';
   LcdShowStr(6, 1,P_buff);
   }
   else if(moshi == 2)	 //��������Ũ������ģʽ
   {
   C_buff[0] = C_baojing/100+0x30;
   C_buff[1] = C_baojing%100/10+0x30;
   C_buff[2] = C_baojing%10+0x30;
   C_buff[4] = '\0';
   LcdShowStr(6, 1,C_buff);
   }				                                                                           
 }
}
/* ������ת��Ϊ�ַ�����str-�ַ���ָ�룬dat-��ת����������ֵ-�ַ������� */
unsigned char IntToString(unsigned char *str, int dat)
{
    signed char i = 0;
    unsigned char len = 0;
    unsigned char buf[6];
    
    if (dat < 0)  //���Ϊ����������
	
    {
        dat = -dat;
        *str++ = '-';
        len++;
    }
    do {          //��ת��Ϊ��λ��ǰ��ʮ��������
        buf[i++] = dat % 10;
        dat /= 10;
    } while (dat > 0);
    len += i;     //i����ֵ������Ч�ַ��ĸ���
    while (i-- > 0)   //������ֵת��ΪASCII�뷴�򿽱�������ָ����
    {
        *str++ = buf[i] + '0';
    }

    *str = '\0';  //����ַ���������
    
    return len;   //�����ַ�������
}

/************���п�2�жϴ�����*************/
void UART_2Interrupt(void) interrupt 8
{
	unsigned char UART_data;
	if(S2CON&S2RI)
	{
	  UART_data=S2BUF;
	  if(UART_data==0xFF)
		{
			if((ZE08_receive[0]==0x17)&&(ZE08_receive[1]==0x04))
			{
			   ZE08 = ZE08_receive[3]*256+ZE08_receive[4];			   
			}
		
			ZE08_DATA_count=0;
		}
		else
		{
			ZE08_receive[ZE08_DATA_count]=UART_data;
			ZE08_DATA_count++;
		}
	
	}
	S2CON&=~S2RI;
}
/*------------------------------------------------
    ��ʱ���ж��ӳ��򣨶�ʱ1ms��
------------------------------------------------*/
void Timer0_isr(void) interrupt 1 
{
   static unsigned int s1j;
   TH0=(65536-5000)/256;	 //���¸�ֵ 5ms
   TL0=(65536-5000)%256;
    
    s1j++;   
	if(s1j>=1300)
   {
     s1j = 0;
	 flag_1s = 1;
	 	
    }

}
