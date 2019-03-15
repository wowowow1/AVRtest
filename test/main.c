/**********************************************
按键控制LED流水灯且闪烁V2.0
更新：在LED熄灭时也可以切换，且T1中断函数不会
再占用CPU。
不足：LED的闪烁仍和外部中断有关联
**********************************************/
#include "iom8515.h"
#include "iomacro.h"
#include "delay.h"
#define uchar unsigned char
#define uint  unsigned int
uchar j,k = 0;
int m = 0;

#pragma vector = INT1_vect         //设置INT0中断向量
__interrupt void LED_right(void)   //按键1中断函数
      {
        m++;
        if(m>7)                    
        { 
          m = 0;                   //当移到最右后跳回最左
        }
        PORTA = (1<<m);
        j = PORTA;                 //更新PORTA的值
        Delay_Ms(5);
        k = 0;                     //缩短切换后的亮灯时间
      }

#pragma vector = INT0_vect         //设置INT1中断向量
__interrupt void LED_left(void)    //按键2中断函数
     {
        m--;
        if(m==(-1))
        {
          m = 7;                   //当移到最左后跳回最右
        }
        PORTA = (1<<m);
        j = PORTA;                 //更新PORTA的值
        Delay_Ms(5);
        k = 0;                     //缩短切换后的亮灯时间
     }

#pragma vector = TIMER1_OVF_vect         //定时器1控制单个LED闪烁
__interrupt void LED_delay_flash(void)
    {
      if(k)
      {
        PORTA = j;           //亮灯
        k++;
      }
      else
      {
        PORTA = 0x00;        //灭灯
        k--;
      }
      TCNT1H = 0x7F;         //定时器1置数
      TCNT1L = 0xFF;
    }
void main(void)
{
  DDRA = 0xFF;          //PORTA口设置为输出
  PORTA = 0x01;         //PA0口设为高电平
  j = PORTA;            //保存初始PORTA的值
  GICR |= 0xC0;         //INT0、INT1中断使能
  MCUCR = 0x0A;         //设置INT0、INT1中断触发方式为下降沿
  GIFR = 0xC0;          //清零INT0、INT1中断标志位
  SREG = 0x80;          //打开全局中断使能
  TCCR1B = 0x04;        //设置T1时钟源为256分频
  TIMSK = 0x80;         //定时器1中断使能
  TCNT1H = 0x7F;        //定时器1置数32767
  TCNT1L = 0xFF;
}