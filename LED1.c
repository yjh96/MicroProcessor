/*
 * LED1.c
 *
 * Created: 2019-03-12 오전 10:55:00
 * Author: TG
 */

#include <mega128.h>
#include <delay.h>
#define LED1 PORTA.0
#define ROUND 10
int n;
void main(void)
{
    PORTA = 0x00; // LED 꺼짐
    DDRA = 0xff;
    while (1)
    {
      for ( n=0; n<ROUND ; n++){
      PORTA =  PORTA | 0x01; 
      delay_ms (1000);
      PORTA = 0x00;
      delay_ms(1000);
    }               
    PORTA = ~PORTA;
    }
}
