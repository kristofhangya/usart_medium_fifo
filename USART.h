#ifndef USART_H_INCLUDED
#define USART_H_INCLUDED

#define recive_buffer_size 128
#define transmit_buffer_size 16

void USART_Init( unsigned int ubrr );
void USART_Transmit( unsigned char data );
unsigned char USART_Receive( void );

#endif // USART_H_INCLUDED
