#include "FIFO.h"

void fifo_init(FIFO* f,uint8_t* data ,uint8_t size){
    f->data = data;
    f->fifo_read_P = 0;
    f->fifo_write_P = 0;
    f->fifo_size = size-1;
    f->fifo_elements = 0;
}

uint8_t fifo_receive(FIFO* f){
    if(!f->fifo_elements) return 0;

    uint8_t uiReturn = 0;
    uiReturn = f->data[f->fifo_read_P];

    f->fifo_read_P++;
    f->fifo_read_P %= f->fifo_size;
    f->fifo_elements--;

    return uiReturn;
}

uint8_t fifo_send(FIFO* f,uint8_t data){

    if((f->fifo_size) == (f->fifo_elements)) return 0;

    (f->data[f->fifo_write_P]) = data;

    f->fifo_write_P++;
    f->fifo_write_P %= f->fifo_size;

    f->fifo_elements++;

    return 1;
}
