#define F_CPU 16000000  // 사용하는 CPU 클럭을 설정한다. delay.h를 위해 필요

#include <mega128.h>
#include <delay.h> 

//DDRAM 설정 : 0x80+DDRAM address 값
#define LINE1 0x80  //첫번째 라인의 DDRAM address : 0x00 -> 0x80+0x00
#define LINE2 0xC0  //두번째 라인의 DDRAM address : 0x40 -> 0x80+0x40

//PG2=LCD_EN, PG1=RW, PG0=RS 에 연결
#define CMD_WRITE   0xFC  //명령어쓰기 E=1, RW=0, RS=0
#define CMD_READ    0xFE  //명령어읽기 E=1, RW=1, RS=0
#define DATA_WRITE  0xFD  //데이터쓰기 E=1, RW=0, RS=1
#define DATA_READ   0xFF  //데이터읽기 E=1, RW=1, RS=1
#define LCD_EN      0x04    //PG2에 연결되어 있기 때문에 bit2를 1로 했다.

//LCD에 명령을 쓰기 위한 함수
void LCD_cmd_write(char cmd)
{
  PORTG = CMD_WRITE;    	//PORTG에 RS, RW, E 가 연결되어 있다.
  PORTB = cmd;              //PORTB에 데이터버스가 연결되어 있다.
  PORTG = PORTG^LCD_EN;   	//E 신호를 H->L로 하기 위해
  delay_ms(2);             //LCD 내부 동작시간
}



//LCD에 데이터를 쓰기 위한 함수
void LCD_data_write(char data)
{
  PORTG = DATA_WRITE;    //PORTG에 RS, RW, E 가 연결되어 있다.
  PORTB = data;          //PORTB에 데이터버스가 연결되어 있다.
  PORTG = PORTG^LCD_EN;  //E 신호를 H->L로 하기 위해
  delay_ms(2);          //LCD 내부 동작시간
}


// LCD 초기화, 초기화 강좌의 순서도 참조
void init_LCD(void)
{
  delay_ms(15);        //15msec 이상 시간지연
 LCD_cmd_write(0x38); //기능셋(데이터버스 8비트, 라인수:2줄)

 LCD_cmd_write(0x01);  //화면 지우기
 LCD_cmd_write(0x06);  //엔트리모드셋
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
  DDRG = 0xFF;  //LCD 컨트롤 신호(PG2=LCD_EN, PG1=RW, PG0=RS)
  PORTG = 0xFF;
}

void main(void)
{
  init_system();  //초기화
  init_LCD();

 LCD_wr_string(LINE1, " Microprocessor  "); //LINE을 지정하고 문자열을 쓴다.
 LCD_wr_string(LINE2, " LCD Test       ");  //LINE을 지정하고 문자열을 쓴다.

  while(1);
}
