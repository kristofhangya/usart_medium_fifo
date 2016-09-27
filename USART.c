#include "USART.h"
#include <avr/interrupt.h>
#include "FIFO.h"

static FIFO recieve, transmit;
static uint8_t r[recive_buffer_size],t[transmit_buffer_size];

void USART_Init( unsigned int ubrr )
{
/* Set baud rate */
UBRR0H = (unsigned char)(ubrr>>8);
UBRR0L = (unsigned char)ubrr;
/* Enable receiver and transmitter */
UCSR0B = (1<<RXEN)|(1<<TXEN) | (1<< RXCIE0);
/* Set frame format: 8data, 2stop bit */
UCSR0C = (1<<USBS)|(3<<UCSZ0);

    fifo_init(&recieve,r,recive_buffer_size);
    fifo_init(&transmit,t,transmit_buffer_size);
}

void USART_Transmit( unsigned char data ){
    fifo_send(&transmit,data);
    UCSR0B |= (1 << UDRIE0);

}
unsigned char USART_Receive( void ){
   return fifo_receive(&recieve);
}

ISR(USART0_RX_vect){
    fifo_send(&recieve,UDR0);
}

ISR(USART0_UDRE_vect){
    if(!transmit.fifo_elements){ //tilt
        UCSR0B &= ~(1 << UDRIE0);
    }else{
        UDR0 = fifo_receive(&transmit);
    }
}
