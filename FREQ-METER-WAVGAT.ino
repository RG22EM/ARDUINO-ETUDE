/*
 * 
 */
#include "lgtx8p.h"
 
#define int_on() PCMSK1=(1<<PCINT9)|(1<<PCINT10)|(1<<PCINT11); PCICR=(1<<PCIE1);
//включить прерывание PCINT1, выбор пинов прерывания A1,A2,A3
#define int_off() PCMSK1=0; PCICR=0; //отключить PCINT1

volatile uint16_t int_tic=0;
unsigned int old_time = 0;

#include <LCD5110_SSVS.h>
#include <avr/delay.h>

extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
LCD5110 lcd(10,11,12,13);
#define F_CPU 32E6 //нужно указать фактическую частоту МК 

ISR (TIMER1_OVF_vect){ int_tic++; } // прерывание частотомера

void freq_meter(){
   lcd.clrScr();
   lcd.setFont(SmallFont);
   lcd.print("Freq.counter",LEFT, 0);
  int_on();//включить прерывание PCINT1
  TIMSK1 = 1<<TOIE1;// подключить прерывание
  uint32_t freqm=0;// Переменная измерения частоты
  int_tic=0; TCNT1=0; TIFR1=0;//всё обнулить
while(1){
   TCCR1B=7;//тактирование от входа Т1
   delay(2000); TCCR1B=0;
   freqm= (((uint32_t)int_tic<<16) | TCNT1)/2; //сложить что натикало
   int_tic=0; TCNT1 = 0; 
   lcd.clrScr(); lcd.setFont(SmallFont);
   lcd.print("Freq.counter",LEFT, 0);
   lcd.setFont(MediumNumbers);
   if (freqm <10000) { lcd.printNumI(freqm, CENTER, 8); lcd.setFont(SmallFont); lcd.print("Herz",CENTER, 32 ); }
   if (freqm >=10000u && freqm < 1000000ul ) { lcd.printNumF( ((float)freqm/1000),3 ,CENTER, 8);lcd.setFont(SmallFont);  lcd.print("KiloHerz",CENTER, 32 ); }
   if (freqm >=1000000ul ) { lcd.printNumF( ((float)freqm/1000000ul),3 ,CENTER, 8); lcd.setFont(SmallFont); lcd.print("MegaHerz",CENTER, 32 ); }    
   }  
 }

//////////////////////////////////////////////////////////////////////

void setup() {
 pinMode(4,OUTPUT);
 digitalWrite(4,LOW);
 // CLKPR = 1<<PMCE;//разрешить изменение частоты кварца
 // CLKPR = B00000000;
 // delay(2000);
  
 lcd.InitLCD();
 PORTD=0; DDRD=0; TCCR1A=0; TCCR1B=0; TIMSK1=0; 
 DDRB|=1<<PB0; // 8 пин -включение подсветки дисплея = выход
}

void loop() {
if(millis()-old_time >= 10000){
  freq_meter();
  old_time=millis();
  }
}
