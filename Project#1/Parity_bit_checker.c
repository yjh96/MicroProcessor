#include <mega128.h>
#include <delay.h>

int STATUS, c;

void main(void)

{
    DDRA = 0b00000001; // 8 A ports for output
    DDRG = 0b00000011; // 8 B ports for output
    PORTA = 0xff; // Initially all OFF
    DDRB = 0x00; // 8 B ports for input
    DDRD = 0x00; // 8 D ports for input
        while (1) {
            STATUS = 0;
            c = 0;

            // Check Data From PINB.
            /*
            *for문을 사용하지 않은 이유는 PINB.k와 같은 변수를 이용해 해당 핀을 자정할 수                       *없었습니다.
            *PIN을 지정하기 위해서는 CONSTANT 값을 요구하기 때문입니다.
            */
            if(PINB.0 == 1){ c = c+1; }
            if(PINB.1 == 1){ c = c+1; }
            if(PINB.2 == 1){ c = c+1; }
            if(PINB.3 == 1){ c = c+1; }
            if(PINB.4 == 1){ c = c+1; }
            if(PINB.5 == 1){ c = c+1; }
            if(PINB.6 == 1){ c = c+1; }
            if(PINB.7 == 1){ c = c+1; }

            //Select Parity mode. EVEN = 1, ODD =0
            if(PIND.0 == 1) { STATUS = 1; }
            if(PIND.0 == 0) { STATUS = 0; }

            //Check Odd Parity

            if((c%2 == 0)&& (STATUS == 0)){
              PORTA = 0x00;
              delay_ms(200);
              PORTA = 0xFF;
              delay_ms(200);
             }

            //Check Even Parity
            else if((c%2 == 1)&& (STATUS == 1)){
              PORTA = 0x00;
              delay_ms(200);
              PORTA = 0xFF;
              delay_ms(200);
             }

            // If data have Error, nocite Error LED to blink
            else {
                PORTA = 0xff;       // OFF PA0
                PORTG = 0b00000010; // Flash pattern 1
                delay_ms(200);
                PORTG = 0b00000001;
                delay_ms(200);
                PORTG = 0xFF;       // OFF PG0, PG1
             }

            // End switch
            if (PIND.1 == 0 )  //check switch status
            {
                PORTA = 0xFF;
                break;          //end of program
             }
        }
}
