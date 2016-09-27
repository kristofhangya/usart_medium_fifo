#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED
#include "inttypes.h"

typedef struct{

    uint8_t* data;
    uint8_t fifo_size;
    uint8_t fifo_write_P;
    uint8_t fifo_read_P;
    uint8_t fifo_elements;

}FIFO;

void fifo_init(FIFO*,uint8_t*,uint8_t);
uint8_t fifo_receive(FIFO*);
uint8_t fifo_send(FIFO*,uint8_t);


#endif // FIFO_H_INCLUDED
