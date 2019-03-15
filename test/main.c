/**********************************************
��������LED��ˮ������˸V2.0
���£���LEDϨ��ʱҲ�����л�����T1�жϺ�������
��ռ��CPU��
���㣺LED����˸�Ժ��ⲿ�ж��й���
**********************************************/
#include "iom8515.h"
#include "iomacro.h"
#include "delay.h"
#define uchar unsigned char
#define uint  unsigned int
uchar j,k = 0;
int m = 0;

#pragma vector = INT1_vect         //����INT0�ж�����
__interrupt void LED_right(void)   //����1�жϺ���
      {
        m++;
        if(m>7)                    
        { 
          m = 0;                   //���Ƶ����Һ���������
        }
        PORTA = (1<<m);
        j = PORTA;                 //����PORTA��ֵ
        Delay_Ms(5);
        k = 0;                     //�����л��������ʱ��
      }

#pragma vector = INT0_vect         //����INT1�ж�����
__interrupt void LED_left(void)    //����2�жϺ���
     {
        m--;
        if(m==(-1))
        {
          m = 7;                   //���Ƶ��������������
        }
        PORTA = (1<<m);
        j = PORTA;                 //����PORTA��ֵ
        Delay_Ms(5);
        k = 0;                     //�����л��������ʱ��
     }

#pragma vector = TIMER1_OVF_vect         //��ʱ��1���Ƶ���LED��˸
__interrupt void LED_delay_flash(void)
    {
      if(k)
      {
        PORTA = j;           //����
        k++;
      }
      else
      {
        PORTA = 0x00;        //���
        k--;
      }
      TCNT1H = 0x7F;         //��ʱ��1����
      TCNT1L = 0xFF;
    }
void main(void)
{
  DDRA = 0xFF;          //PORTA������Ϊ���
  PORTA = 0x01;         //PA0����Ϊ�ߵ�ƽ
  j = PORTA;            //�����ʼPORTA��ֵ
  GICR |= 0xC0;         //INT0��INT1�ж�ʹ��
  MCUCR = 0x0A;         //����INT0��INT1�жϴ�����ʽΪ�½���
  GIFR = 0xC0;          //����INT0��INT1�жϱ�־λ
  SREG = 0x80;          //��ȫ���ж�ʹ��
  TCCR1B = 0x04;        //����T1ʱ��ԴΪ256��Ƶ
  TIMSK = 0x80;         //��ʱ��1�ж�ʹ��
  TCNT1H = 0x7F;        //��ʱ��1����32767
  TCNT1L = 0xFF;
}