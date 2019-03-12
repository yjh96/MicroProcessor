/*
 * LED1.c
 *
 * Created: 2019-03-12 오전 10:55:00
 * Author: TG
 */

#include <mega128.h>
#include <delay.h>
#define LED1 PORTA.0

void main(void)
{
    int tmp = 0;
    DDRA = 0xff;
    while (1)
    {
        PORTA = 0x02;                  //LED 꺼짐
        delay_ms(100);
        tmp = tmp + 1;
        PORTA = 0xff;                  //LED 켜짐
        delay_ms(100);
        
        if ( tmp == 10 ){
            PORTA = 0x00;
            delay_ms(1000);
            PORTA = 0xff;
            delay_ms(1000);
            tmp = 0;
            }
         
    }
}
