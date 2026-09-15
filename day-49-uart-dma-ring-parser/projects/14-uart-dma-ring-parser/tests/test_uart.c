#include <assert.h>
#include "uart/uart_protocol.h"
int main(){uart_ring_t r;uint8_t v;uart_ring_init(&r);for(int i=0;i<4;i++)assert(uart_ring_push(&r,i));for(int i=0;i<4;i++){assert(uart_ring_pop(&r,&v));assert(v==(uint8_t)i);}uint8_t f[]={0xAA,0x01,0x02,0x10,0x20,0x33};uart_frame_t o;assert(uart_parse_frame(f,sizeof(f),&o)==UART_OK&&o.type==1&&o.length==2);f[5]=0x44;assert(uart_parse_frame(f,sizeof(f),&o)==UART_ERR_CRC);return 0;}
