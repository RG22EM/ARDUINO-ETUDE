/* Генератор с регулируемой частотой и скважностью  v 2.5
 *  предназначен только для МК lgt8f328p 
 * Распиновка: Энкодер пин A0,A1  (PC0,PC1)
 * Кнопка энкодера пин 2 (PD2) 
 * Дисплей nokia 5110 - 13,12,11,10 (PB5,PB4,PB3,PB2)
 *  Выход генератора DDS пин 4 (PD4)     
 *  Выход генератора PWM пин 9 (PB1)  
 *  Вход вольтметра  пин A3 (ADC3)
 *  Вход частотометра пин 5 (PD5) 
 */ 



const PROGMEM uint8_t  sinewave[]= // массив синуса
{
0x80,0x83,0x86,0x89,0x8c,0x8f,0x92,0x95,0x98,0x9c,0x9f,0xa2,0xa5,0xa8,0xab,0xae,
0xb0,0xb3,0xb6,0xb9,0xbc,0xbf,0xc1,0xc4,0xc7,0xc9,0xcc,0xce,0xd1,0xd3,0xd5,0xd8,
0xda,0xdc,0xde,0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xec,0xed,0xef,0xf0,0xf2,0xf3,0xf5,
0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfc,0xfd,0xfe,0xfe,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xfe,0xfe,0xfd,0xfc,0xfc,0xfb,0xfa,0xf9,0xf8,0xf7,
0xf6,0xf5,0xf3,0xf2,0xf0,0xef,0xed,0xec,0xea,0xe8,0xe6,0xe4,0xe2,0xe0,0xde,0xdc,
0xda,0xd8,0xd5,0xd3,0xd1,0xce,0xcc,0xc9,0xc7,0xc4,0xc1,0xbf,0xbc,0xb9,0xb6,0xb3,
0xb0,0xae,0xab,0xa8,0xa5,0xa2,0x9f,0x9c,0x98,0x95,0x92,0x8f,0x8c,0x89,0x86,0x83,
0x80,0x7c,0x79,0x76,0x73,0x70,0x6d,0x6a,0x67,0x63,0x60,0x5d,0x5a,0x57,0x54,0x51,
0x4f,0x4c,0x49,0x46,0x43,0x40,0x3e,0x3b,0x38,0x36,0x33,0x31,0x2e,0x2c,0x2a,0x27,
0x25,0x23,0x21,0x1f,0x1d,0x1b,0x19,0x17,0x15,0x13,0x12,0x10,0x0f,0x0d,0x0c,0x0a,
0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x03,0x02,0x01,0x01,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x01,0x02,0x03,0x03,0x04,0x05,0x06,0x07,0x08,
0x09,0x0a,0x0c,0x0d,0x0f,0x10,0x12,0x13,0x15,0x17,0x19,0x1b,0x1d,0x1f,0x21,0x23,
0x25,0x27,0x2a,0x2c,0x2e,0x31,0x33,0x36,0x38,0x3b,0x3e,0x40,0x43,0x46,0x49,0x4c,
0x4f,0x51,0x54,0x57,0x5a,0x5d,0x60,0x63,0x67,0x6a,0x6d,0x70,0x73,0x76,0x79,0x7c
};

const PROGMEM uint8_t squarewave[]= //массив меандра
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,0xff,
};

const PROGMEM uint8_t trianglewave[]= //массив треугольника
{
0x00,0x02,0x04,0x06,0x08,0x0a,0x0c,0x0e,0x10,0x12,0x14,0x16,0x18,0x1a,0x1c,0x1e,
0x20,0x22,0x24,0x26,0x28,0x2a,0x2c,0x2e,0x30,0x32,0x34,0x36,0x38,0x3a,0x3c,0x3e,
0x40,0x42,0x44,0x46,0x48,0x4a,0x4c,0x4e,0x50,0x52,0x54,0x56,0x58,0x5a,0x5c,0x5e,
0x60,0x62,0x64,0x66,0x68,0x6a,0x6c,0x6e,0x70,0x72,0x74,0x76,0x78,0x7a,0x7c,0x7e,
0x80,0x82,0x84,0x86,0x88,0x8a,0x8c,0x8e,0x90,0x92,0x94,0x96,0x98,0x9a,0x9c,0x9e,
0xa0,0xa2,0xa4,0xa6,0xa8,0xaa,0xac,0xae,0xb0,0xb2,0xb4,0xb6,0xb8,0xba,0xbc,0xbe,
0xc0,0xc2,0xc4,0xc6,0xc8,0xca,0xcc,0xce,0xd0,0xd2,0xd4,0xd6,0xd8,0xda,0xdc,0xde,
0xe0,0xe2,0xe4,0xe6,0xe8,0xea,0xec,0xee,0xf0,0xf2,0xf4,0xf6,0xf8,0xfa,0xfc,0xfe,
0xff,0xfd,0xfb,0xf9,0xf7,0xf5,0xf3,0xf1,0xef,0xef,0xeb,0xe9,0xe7,0xe5,0xe3,0xe1,
0xdf,0xdd,0xdb,0xd9,0xd7,0xd5,0xd3,0xd1,0xcf,0xcf,0xcb,0xc9,0xc7,0xc5,0xc3,0xc1,
0xbf,0xbd,0xbb,0xb9,0xb7,0xb5,0xb3,0xb1,0xaf,0xaf,0xab,0xa9,0xa7,0xa5,0xa3,0xa1,
0x9f,0x9d,0x9b,0x99,0x97,0x95,0x93,0x91,0x8f,0x8f,0x8b,0x89,0x87,0x85,0x83,0x81,
0x7f,0x7d,0x7b,0x79,0x77,0x75,0x73,0x71,0x6f,0x6f,0x6b,0x69,0x67,0x65,0x63,0x61,
0x5f,0x5d,0x5b,0x59,0x57,0x55,0x53,0x51,0x4f,0x4f,0x4b,0x49,0x47,0x45,0x43,0x41,
0x3f,0x3d,0x3b,0x39,0x37,0x35,0x33,0x31,0x2f,0x2f,0x2b,0x29,0x27,0x25,0x23,0x21,
0x1f,0x1d,0x1b,0x19,0x17,0x15,0x13,0x11,0x0f,0x0f,0x0b,0x09,0x07,0x05,0x03,0x01
};

const PROGMEM uint8_t sawtoothwave[]= //массив пила1
{
0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f,
0x10,0x11,0x12,0x13,0x14,0x15,0x16,0x17,0x18,0x19,0x1a,0x1b,0x1c,0x1d,0x1e,0x1f,
0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x28,0x29,0x2a,0x2b,0x2c,0x2d,0x2e,0x2f,
0x30,0x31,0x32,0x33,0x34,0x35,0x36,0x37,0x38,0x39,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,
0x40,0x41,0x42,0x43,0x44,0x45,0x46,0x47,0x48,0x49,0x4a,0x4b,0x4c,0x4d,0x4e,0x4f,
0x50,0x51,0x52,0x53,0x54,0x55,0x56,0x57,0x58,0x59,0x5a,0x5b,0x5c,0x5d,0x5e,0x5f,
0x60,0x61,0x62,0x63,0x64,0x65,0x66,0x67,0x68,0x69,0x6a,0x6b,0x6c,0x6d,0x6e,0x6f,
0x70,0x71,0x72,0x73,0x74,0x75,0x76,0x77,0x78,0x79,0x7a,0x7b,0x7c,0x7d,0x7e,0x7f,
0x80,0x81,0x82,0x83,0x84,0x85,0x86,0x87,0x88,0x89,0x8a,0x8b,0x8c,0x8d,0x8e,0x8f,
0x90,0x91,0x92,0x93,0x94,0x95,0x96,0x97,0x98,0x99,0x9a,0x9b,0x9c,0x9d,0x9e,0x9f,
0xa0,0xa1,0xa2,0xa3,0xa4,0xa5,0xa6,0xa7,0xa8,0xa9,0xaa,0xab,0xac,0xad,0xae,0xaf,
0xb0,0xb1,0xb2,0xb3,0xb4,0xb5,0xb6,0xb7,0xb8,0xb9,0xba,0xbb,0xbc,0xbd,0xbe,0xbf,
0xc0,0xc1,0xc2,0xc3,0xc4,0xc5,0xc6,0xc7,0xc8,0xc9,0xca,0xcb,0xcc,0xcd,0xce,0xcf,
0xd0,0xd1,0xd2,0xd3,0xd4,0xd5,0xd6,0xd7,0xd8,0xd9,0xda,0xdb,0xdc,0xdd,0xde,0xdf,
0xe0,0xe1,0xe2,0xe3,0xe4,0xe5,0xe6,0xe7,0xe8,0xe9,0xea,0xeb,0xec,0xed,0xee,0xef,
0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9,0xfa,0xfb,0xfc,0xfd,0xfe,0xff
};

const PROGMEM uint8_t rewsawtoothwave[]= //массив пила2
{
0xff,0xfe,0xfd,0xfc,0xfb,0xfa,0xf9,0xf8,0xf7,0xf6,0xf5,0xf4,0xf3,0xf2,0xf1,0xf0,
0xef,0xee,0xed,0xec,0xeb,0xea,0xe9,0xe8,0xe7,0xe6,0xe5,0xe4,0xe3,0xe2,0xe1,0xe0,
0xdf,0xde,0xdd,0xdc,0xdb,0xda,0xd9,0xd8,0xd7,0xd6,0xd5,0xd4,0xd3,0xd2,0xd1,0xd0,
0xcf,0xce,0xcd,0xcc,0xcb,0xca,0xc9,0xc8,0xc7,0xc6,0xc5,0xc4,0xc3,0xc2,0xc1,0xc0,
0xbf,0xbe,0xbd,0xbc,0xbb,0xba,0xb9,0xb8,0xb7,0xb6,0xb5,0xb4,0xb3,0xb2,0xb1,0xb0,
0xaf,0xae,0xad,0xac,0xab,0xaa,0xa9,0xa8,0xa7,0xa6,0xa5,0xa4,0xa3,0xa2,0xa1,0xa0,
0x9f,0x9e,0x9d,0x9c,0x9b,0x9a,0x99,0x98,0x97,0x96,0x95,0x94,0x93,0x92,0x91,0x90,
0x8f,0x8e,0x8d,0x8c,0x8b,0x8a,0x89,0x88,0x87,0x86,0x85,0x84,0x83,0x82,0x81,0x80,
0x7f,0x7e,0x7d,0x7c,0x7b,0x7a,0x79,0x78,0x77,0x76,0x75,0x74,0x73,0x72,0x71,0x70,
0x6f,0x6e,0x6d,0x6c,0x6b,0x6a,0x69,0x68,0x67,0x66,0x65,0x64,0x63,0x62,0x61,0x60,
0x5f,0x5e,0x5d,0x5c,0x5b,0x5a,0x59,0x58,0x57,0x56,0x55,0x54,0x53,0x52,0x51,0x50,
0x4f,0x4e,0x4d,0x4c,0x4b,0x4a,0x49,0x48,0x47,0x46,0x45,0x44,0x43,0x42,0x41,0x40,
0x3f,0x3e,0x3d,0x3c,0x3b,0x3a,0x39,0x38,0x37,0x36,0x35,0x34,0x33,0x32,0x31,0x30,
0x2f,0x2e,0x2d,0x2c,0x2b,0x2a,0x29,0x28,0x27,0x26,0x25,0x24,0x23,0x22,0x21,0x20,
0x1f,0x1e,0x1d,0x1c,0x1b,0x1a,0x19,0x18,0x17,0x16,0x15,0x14,0x13,0x12,0x11,0x10,
0x0f,0x0e,0x0d,0x0c,0x0b,0x0a,0x09,0x08,0x07,0x06,0x05,0x04,0x03,0x02,0x01,0x00,
};


const PROGMEM char musor_mass[]= //массив для подгонки адреса в флэш-памяти
{
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

// пользовательские настройки переменных по умолчанию
//режимы 0-синус dds, 1-треугольник dds, 2-меандр dds, 3 пила1 dds, 4 пила2 dds
//5- гегулировка частоты pwm, 6- Duty pwm, 7-частотометр, 8 -вольтметр
volatile uint8_t regim=7; //выбор режима генератора по умолчанию 
volatile int32_t freq=1000;// частота по умолчанию
volatile uint16_t shag=100; //шаг энкодера по умолчанию
#define dac_trim 5 //  настройка выходного уровня ЦАП
// 0 -переменный резистор на пине aref, 1 -1.024V; 2-2.048v; 4-4.096V; 5-Vcc
#define F_CPU 32E6 //нужно указать фактическую частоту МК 


volatile uint16_t int_tic=0;//переменная частотометра (переполнение таймера) 
uint16_t Vbg, involt;//переменные вольтметра
volatile uint32_t icr=0;  //переменная для управления регистром сравнения таймера1
volatile uint8_t monitor_flag; // флаг для вывода на дисплей
volatile uint8_t duty=50; //скважность по умолчанию
//volatile uint8_t main_flag=0;//флаг работа в режиме генератора или нет
volatile uint8_t modebit=1;//флаг смены режимов.(для анализа действия энкодера)
#include "lgtx8p.h"
#define int_on() PCMSK1=(1<<PCINT9); PCICR=(1<<PCIE1); EIMSK=1<<INT0; //прерывание на А1
//включить прерывание PCINT1, выбор пинов прерывания A1,
#define int_off() PCMSK1=0; PCICR=0; EIMSK=0; ///отключить прерывания энкодера и кнопки
#include <LCD5110_SSVS.h>
#include <avr/delay.h>
extern uint8_t SmallFont[];
extern uint8_t MediumNumbers[];
LCD5110 lcd(10,11,12,13);

// DDS algorithm 
static inline void signalOUT(uint16_t ad01,uint8_t ad2, const uint8_t *wvt){ 
 asm volatile(  
  "ldi r28,0xA1; "            "\n\t" 
   "clr r29;"                     "\n\t" 
    "eor r18, r18;"            "\n\t"
    "eor r19, r19;"            "\n\t"
     "1:"                            "\n\t"
     "add r18, %A0;"        "\n\t" 
     "adc r19, %B0;"        "\n\t" 
     "adc %A2, %1;"        "\n\t" 
     "lpm      ;"                 "\n\t" 
    "st Y, __tmp_reg__  ;" "\n\t" 
   "sbis %3, 7   ;"           "\n\t" 
  "rjmp 1b;"                  "\n\t" 
 ::"r" (ad01),"r" (ad2),"e" (wvt), "I" (_SFR_IO_ADDR(PORTF))
 :"r18", "r19","r28", "r29" );
}

void setup(){
lcd.InitLCD();
for (int n=0; n <sizeof(musor_mass); n++ ) {PORTF=musor_mass[n]&0xFC; }   
pinMode(A0,INPUT_PULLUP); //encoder
pinMode(A1,INPUT_PULLUP); // encoder
pinMode(2,INPUT_PULLUP); //encoder key
pinMode(3,OUTPUT);// buzzer
TCCR1A=0; TCCR1B=0; TIMSK1=0; 
EICRA=3; //INT0 -RISING+FALLING 
EIFR==EIFR; //flag clear
TCCR0B=0;  check_regim(); 
//разгон до 32 МГц от внутреннего RC генератора
CLKPR = 1<<PMCE;//разрешить изменение
CLKPR = 0; //делитель =1
} //end setup


        
/////////////// ПРЕРЫВАНИЕ от кн0пки//////////////////////////         
ISR (INT0_vect){ // прерывание от кнопки энкодера 
int_off();
if ( (TIFR3&(1<<0))==0 ){TIFR3|=1<<0;} // флаг выходы из режима частотометра
if (!modebit) { modebit=1; int_on(); return;} //меняли режим, просто выйти
if (regim==6) { regim=5; check_regim();  return; }
          switch (shag){ 
                   case 1: shag=10;     break;
                   case 10: shag=100;    break;
                   case 100: shag=1000;   break;
                   case 1000: shag=1; break; 
                  } check_regim(); return;
            } //конец прерывания *если нажата кнопка энкодера*
////////////////////////////////////////////////////////////
 
 
 ISR (PCINT1_vect){ //прерывание при вращении энкодера
// static boolean n=0;  if (n=!n){return;} // снять ремарку для энкодеров с двойным щелчком
int_off();
 bool x = (PINC&1)^((PINC&2)>>1);
if ( (TIFR3&(1<<0))==0 ){TIFR3|=1<<0;} // флаг выхода из режима частотометра
 //////////////////// переключение режимов при нажатой кнопке//////////////////////
 modebit= (PIND&(1<<2)); //0 -кнопка нажата. 1 -не нажата
         if (!modebit) { //если кнопка нажата
         //флаг что переключаю режимы
       if (x) { regim++; if (regim>8) {regim=0;} }
       else {regim-- ; if (regim>8) {regim=8;}}         
       check_regim(); return;
       }
////////////////// переключение частоты/////////////////////////////////////////
if (TCCR1B==17 && ICR1<2800 && regim==5){ //если > 2800 герц
if(x) {if (icr<1000 && shag > 100) shag=100; 
       if (icr<100 && shag > 10) shag=10;
       if (icr<10 && shag > 1) shag=1;          
       icr-=shag;
         if (icr<2) icr=2;    }//ограничитель
         else {  if (icr > 1800 && shag >100) shag =100; icr+=shag ;  } 
  check_regim(); return;   }
///////////////////////////переключение Duty//////////////////////////////////
if (regim==6){if (ICR1>100){ 
                if (x){if(duty<100) {duty++; }  }
                if (!x){ if(duty>0) {duty--; }} }
              else{ 
                    if (x){if(OCR1A<ICR1) {OCR1A++; }  }         
                    else {if(OCR1A>0) {OCR1A--; }  }         
                    if(OCR1A>ICR1) OCR1A=ICR1-1;
                   
                    duty=(uint32_t)100*OCR1A/ICR1;  }
         check_regim(); return;
     } // end перекл. duty
   x? freq+=shag : freq-=shag ;  //изменение частоты менее 2800 Герц
if (freq < 1) freq=1; check_regim();
} // end isr pcint
         


void pwm_gen(){ //настройка таймера1
 uint16_t divider=1; 
  icr = (uint32_t)(F_CPU / freq /2 /divider); 
   byte shifts[] = {3,3,2,2};
     for(byte i = 0; i < 4; i++){
        if (icr > 65536) {
           divider <<= shifts[i];
           icr = (uint32_t)F_CPU / freq /2 /divider; }
        else {  TCCR1B = (i+1)|(1<<WGM13);  break;  } }
ICR1=icr-1; 
set_duty();
} //end pwm_gen

    
void loop() {
   if (regim <5){ dds_set();} 
   if (regim==7) {freq_meter();}
   if (regim==8) {volt_meter();}
   if (monitor_flag) { monitor_flag=0; monitor_out(); }
 }//end loop


void monitor_out(){
char mystr[14];//массив для вывода строк на дисплей
lcd.clrScr();
//Вывод первой строчки
lcd.setFont(SmallFont);
if (regim<8){
if (freq <1E4) {lcd.print("Frequency, Hz",CENTER,0 );  }
if (freq >=1E4) {lcd.print("Frequency, kHz",CENTER,0 );  }
} if (regim==8){lcd.print("Voltage, Volt",CENTER,0 );  }
//Вывод второй строчки
lcd.setFont(MediumNumbers);
if (regim<8){
if (freq <10000) { lcd.printNumI(freq, CENTER, 8); }
if (freq >=10000u && freq < 1000000ul ) { lcd.printNumF( ((float)freq/1000),3 ,CENTER, 8);  }
if (freq >=1000000ul ) { lcd.printNumF( ((float)freq/1000),2 ,CENTER, 8);  }
} if (regim==8){ lcd.printNumF( ((float)involt/1000),3 ,CENTER, 8);  }
//Вывод третьей строчки
   lcd.setFont(SmallFont);
     switch(regim){ 
       case 0: lcd.print("Sinus DDS",CENTER, 32); break;
        case 1: lcd.print("Triangle DDS",CENTER, 32); break;
         case 2: lcd.print("Meandr DDS",CENTER, 32); break;
        case 3: lcd.print("Pila1 DDS",CENTER, 32); break;
       case 4: lcd.print("Pila2 DDS",CENTER, 32); break;
      case 5: lcd.print("PWM Mode",CENTER,32); break;
    case 6: lcd.print("Duty Mode", CENTER, 32);break;
   case 7: lcd.print("Freq counter", CENTER, 32);break;
  case 8: lcd.print("Volt meter", CENTER, 32);
     }
//Вывод четвёртой строчки  
 if (regim==6) { sprintf(mystr, "Duty=%d %%", duty);
         lcd.print(mystr, CENTER, 40);}
         else if (regim < 6) {sprintf(mystr, "Step=%d", shag);
          lcd.print(mystr, CENTER, 40);}
if (regim==8){
   sprintf(mystr, "Vcc= %d.%02d v", (int)(Vbg/1000), (int)Vbg%1000   );
   lcd.print(mystr, CENTER, 40);
   }//end if regim 8
}
//end monitor out


void set_duty(){
if (regim==6&&ICR1<100) return;
  if (regim==5 && ICR1<100){
    OCR1A=ICR1/2; duty=50; 
    return;   }
   static uint16_t ocr;
 ocr=(uint32_t)ICR1*duty/100;
OCR1A=ocr;
}

void check_regim(){// проверка и установка режимов работы
if (regim <5){ // если DDS режимы:
  if (freq > 100000) { freq=100000;}
    TCCR1B=0; TCCR1A=0;  DDRB&=~(1<<DDB1); // 9 pin arduino set Z-mode 
    }// end if regim <5
  if (regim==5 || regim==6) {// если PWM или Duty 
      TCCR1A=1<<COM1A1; DDRB|=1<<DDB1; // 9 pin set output (pwm out)
      if (TCCR1B==17 && ICR1<2800){ 
              ICR1=icr; freq= F_CPU/2/ICR1;  
              set_duty();                      }
       else { pwm_gen(); } 
         }
   PORTF|= 1<<7; //поставить флаг что-б выйти из цикла DDS, если были в цикле
if (regim==7){ freq=0;} //если частотометр то обнулить частоту
monitor_flag=1;
int_on()

}


ISR (TIMER1_OVF_vect){ int_tic++; } // прерывание частотомера

void freq_meter(){
//подготовка таймера1
TCCR1B=0; TCCR1A=0; TIMSK1 = 1<<TOIE1;// подключить прерывание
 int_tic=0; TCNT1=0; TIFR1=TIFR1;//всё обнулить
  //подготовка таймера3
   TCCR3B=0;TCCR3A=0; TIFR3=TIFR3; 
   //все 3 регистра стравнения что б удобнее смотреть регистр флагов
     uint16_t ocr = ( (uint32_t)F_CPU/1024) -1;
     OCR3AH=ocr>>8; OCR3AL=ocr;// -2 sec
     OCR3BH=ocr>>8; OCR3BL=ocr;// -2 sec
     OCR3CH=ocr>>8; OCR3CL=ocr;// -2 sec  
    TCCR3B=5<<CS30; //старт счёта 2х секунд
   TCCR1B=7<<CS10;//старт счёта таймера1 от тактового входа
  while(TIFR3==0);// крутится пока не будет флагов конца счёта 
 TCCR1B=0;// стоп Тimer1
TIMSK1=0;
if ( (TIFR3&(1<<0))==0){// если не было переполнения, то считаем
 freq= ((uint32_t)int_tic<<16) | TCNT1; //сложить что натикало
  int_tic=0; TCNT1 = 0; 
  } monitor_flag=1;
 }


//////////////////////ВОЛЬТМЕТР/////////////////////////////////
void volt_meter() {
 Vbg=Vbg_read();//измерить напряжение на Vcc
  involt=auto_range_read(3);//измерить на входе А3
 monitor_flag=1;
}//end volt meter


// функция для измерения напряжения с автоматическим переключением референса
uint16_t auto_range_read(uint8_t in){
 uint16_t an_in;
  an_in= _adc(in,3);//вкючение референса 1024
   if (an_in <=(800*4)) {return (an_in/4);} 
    an_in= _adc(in,2); //вкючение референса 2048
    if (an_in <=(1800*2)) {return (an_in/2); } 
    an_in=_adc(in,4); //вкючение референса 4096
   if (an_in <3800) {return an_in; }
  an_in= _adc(in,1);
 an_in= (uint32_t)an_in * Vbg / 4096;
return an_in; 
} 


//////  analog Read (input, reference)
uint16_t _adc( uint8_t in, uint8_t refs){ 
uint16_t adc; ADCSRA=1<<ADEN | 1<<ADPS2 |0<<ADPS1 |1<<ADPS0; // clk /32
 ADCSRB=0; ADCSRC=0; DIDR0=1<<in;
  switch(refs) { //0 -ext, 1-Vcc, 2-2048, 3-1024,  4-4096 
   case 0: ADCSRD=0; break; // AREF ничего не меняется, REFS=0
    case 1: ADCSRD=0;break; // VCC ничего не меняется, REFS=1
   case 2: ADCSRD=0; VCAL=VCAL2; break; // 2v048
   case 3: ADCSRD=0; VCAL=VCAL1; break; // 1v1024
  case 4: refs=0;  ADCSRD=1<<REFS2; VCAL=VCAL3; break; // 4v096  
 }
ADMUX=in&0xF | refs<<6;
 uint32_t akkum=0;
 for (int n=0x0; n<=0xff; n++ ) {
  ADCSRA |= (1<<ADSC);   
  while (ADCSRA&(1<<ADSC));
 akkum += ADC; }
akkum>>=8; 
return (uint16_t)akkum;

}
//функция для измерения напряжения на Vcc
uint16_t Vbg_read(){
ADCSRB=0; ADCSRC=0;
 ADCSRA=1<<ADEN | 1<<ADPS2 |0<<ADPS1 |1<<ADPS0; // adc enable , clk/32
  ADMUX=1<<REFS0 | 1<<3 | 1<<2 | 1<<0; //ref=avcc, input= ivref 
   ADCSRD=1<<BGEN ; //ivref=1v024
    VCAL=VCAL1;//load 1v024 calibrate byte
     uint32_t bgaread=0;
      //собрать 256 семплов для усреднения
     for (int n=0x0; n<=0xff; n++ ) {
     ADCSRA |= (1<<ADSC);   
    while (bit_is_set(ADCSRA,ADSC));
    bgaread += ADC;
   }
  bgaread>>=8; 
 bgaread= ((uint32_t)1024<<12) / bgaread;
return (uint16_t)bgaread;
}

void dds_set(){
                PORTF&= ~(1<<7); //флаг DDS
               switch (dac_trim) {
              case 0:  DACON=1<<DACEN|1<<DAOE|1<<DAVS0; break; 
             case 1:  DACON=1<<DACEN|1<<DAOE|1<<DAVS1; ADCSRD= 1<BGEN; break; 
            case 2:  DACON=1<<DACEN|1<<DAOE|1<<DAVS1; ADCSRD= 1<BGEN|1<<IVSEL0; break; 
           case 4:  DACON=1<<DACEN|1<<DAOE|1<<DAVS1; ADCSRD= 1<BGEN|1<<IVSEL1; break; 
           case 5:  DACON= 1<<DACEN | 1<<DAOE; break; 
           } uint32_t temp=  (float)0x1000000ul / (F_CPU/8ul) * freq;
              switch (regim){ 
               case 0: signalOUT(temp, temp>>16,sinewave); break;
                case 1: signalOUT(temp, temp>>16,trianglewave); break;
                 case 2: signalOUT(temp, temp>>16,squarewave); break;
                   case 3: signalOUT(temp, temp>>16,sawtoothwave); break;
                    case 4: signalOUT(temp, temp>>16,rewsawtoothwave);
                       } //end switch      
}
