
/*****************************************************************************
ÑÓ³Ùº¯Êý
/****************************************************************************/
void Delay_Ms (unsigned int a)
{
	unsigned int i;
	while( a-- != 0)
	{
		for(i = 0; i < 600; i++);
	}
}
void delay1ms()
{
   unsigned char i,j;
	 for(i=0;i<20;i++)
	  for(j=0;j<33;j++)
	   ;
 }
 void delaynms(int n)
 {
   unsigned int i;
	for(i=0;i<n;i++)
	   delay1ms();
}