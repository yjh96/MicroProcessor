#include <mega128.h>
#include <delay.h> 

//DDRAM 설정 : 0x80+DDRAM address 값
#define LINE1 0x80  
#define LINE2 0xC0

//PG2=LCD_EN, PG1=RW, PG0=RS 에 연결
#define CMD_WRITE   0xFC;  //명령어쓰기 E=1, RW=0, RS=0
#define CMD_READ    0xFE;  //명령어읽기 E=1, RW=1, RS=0
#define DATA_WRITE  0xFD;  //데이터쓰기 E=1, RW=0, RS=1
#define DATA_READ   0xFF;  //데이터읽기 E=1, RW=1, RS=1
#define LCD_EN      0x04;    //PG2에 연결되어 있기 때문에 bit2를 1로 했다.

//LCD에 명령을 쓰기 위한 함수
void LCD_cmd_write(char cmd)
{
  PORTC = CMD_WRITE;    	//PORTG에 RS, RW, E 가 연결되어 있다.
  PORTB = cmd;              //PORTB에 데이터버스가 연결되어 있다.
  PORTC = PORTC^LCD_EN;   	//E 신호를 H->L로 하기 위해
  delay_ms(2);             //LCD 내부 동작시간
}



//LCD에 데이터를 쓰기 위한 함수
void LCD_data_write(char data)
{
  PORTC = DATA_WRITE;    //PORTG에 RS, RW, E 가 연결되어 있다.
  PORTB = data;          //PORTB에 데이터버스가 연결되어 있다.
  PORTC = PORTC^LCD_EN;  //E 신호를 H->L로 하기 위해
  delay_ms(2);          //LCD 내부 동작시간
}


void font() 
{
    unsigned int i;
    unsigned int font[] = {
        0x00, 0x00, 0x0a, 0x00, 0x11, 0x11, 0x0e, 0x00, // 0x00
        0x0c,0x16,0x1f,0x0f,0x07,0x0f,0x1e,0x0c //0x01
        };
        
    LCD_cmd_write(0x40);
    for (i=0;i<56;i++) LCD_data_write(font[i]);    
}

// LCD 초기화, 초기화 강좌의 순서도 참조
void init_LCD(void)
{
  delay_ms(15);        //15msec 이상 시간지연
 LCD_cmd_write(0x38); //기능셋(데이터버스 8비트, 라인수:2줄)

 LCD_cmd_write(0x01);  //화면 지우기
 LCD_cmd_write(0x06);  //엔트리모드셋
 font();
 LCD_cmd_write(0x0C);  //표시 On
}
// LCD에 문자열을 표시하기 위한 함수
void LCD_wr_string(char d_line, char *lcd_str)
{
 LCD_cmd_write(d_line);      //문자열을 표시하기 위한 라인 설정
 while(*lcd_str != '\0')
 {
  LCD_data_write(*lcd_str);  //한개의 문자씩 LCD에 표시한다.
  lcd_str++;
 }
}
         
// ATmega128의 포트 초기화
void init_system(void)
{
  DDRB = 0xFF;  //LCD 데이터 버스
  PORTB = 0xFF;
  DDRC = 0xFF;  //LCD 컨트롤 신호(PG2=LCD_EN, PG1=RW, PG0=RS)
  PORTC = 0xFF;
}



void main(void)
{
  init_system();  //초기화
  init_LCD();
   

 // 임의의 문자열 출력 
 LCD_cmd_write(LINE2);
 LCD_data_write(0x00);
 LCD_data_write(0x01);
 
  while(1);
  
}
