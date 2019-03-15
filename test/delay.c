/************************************************

16M¾§ÕñÑÓ³ÙÈÎÒâus

************************************************/
void Delay_us(unsigned int us)
{
   unsigned int i;
  i = us;
  i--;
  asm("nop"); asm("nop");
    for(;i!=0;i--)      
    {
          asm("nop");     asm("nop");     asm("nop");
          asm("nop");     asm("nop");     asm("nop");
          asm("nop");     asm("nop");     asm("nop");
    }
   
}
/***********************************************

16M¾§ÕñÑÓ³ÙÈÎÒâms

***********************************************/ 
void Delay_Ms(unsigned int t)
{  
    for(;t>0;t--)      
          Delay_us(1100);
}