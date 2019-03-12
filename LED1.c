/*
 * LED1.c
 *
 * Created: 2019-03-12 오전 10:55:00
 * Author: TG
 */

#include <mega128.h>
#include <delay.h> // Delay 헤더파일 
#define LED1 PORTA.0 // LED1 을 PORTA.0 으로 정의함.

void main(void)
{
    PORTA = 0x00;
    DDRA = 0xff;
    while (1)
    {
        PORTA = 0xff;                  //LED 꺼짐
        delay_ms(500);
        PORTA = 0x00;                  //LED 켜짐
        delay_ms(500);
    }
}
