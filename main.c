#define F_CPU 8000000UL
#define BAUD 9600
#define MYUBRR F_CPU/16/BAUD-1
#include <avr/io.h>
#include <avr/iom128.h>
#include <util/delay.h>
#include "lcd.h"
#include "FIFO.h"
#include <avr/interrupt.h>
#include "USART.h"

uint8_t sent_commands();

int main(){
    _delay_ms(500);
    _delay_ms(500);
    _delay_ms(500);

    LCD_init();



    USART_Init(MYUBRR);

    uint8_t tmp;
    sei();

    while(1){

        if(tmp = USART_Receive()){
            LCD_data(tmp);
            USART_Transmit(tmp);
        }
    }


    return 0;
}




