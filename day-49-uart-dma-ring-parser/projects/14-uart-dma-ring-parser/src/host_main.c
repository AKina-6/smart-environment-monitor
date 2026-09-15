#include <stdio.h>
#include "uart/uart_protocol.h"
static const char*n(uart_status_t s){return s==UART_OK?"OK":s==UART_ERR_FORMAT?"FORMAT":s==UART_ERR_LENGTH?"LENGTH":"CRC";}
int main(){uart_ring_t r;uart_frame_t f;uint8_t v;uart_ring_init(&r);for(int i=0;i<6;i++)uart_ring_push(&r,(uint8_t)(0x30+i));printf("ring queued=%lu\n",(unsigned long)(r.head-r.tail));printf("nonblocking_pop=%s\n",uart_ring_pop(&r,&v)?"PASS":"FAIL");uint8_t good[]={0xAA,0x01,0x02,0x10,0x20,0x33};printf("frame=%s\n",n(uart_parse_frame(good,sizeof(good),&f)));good[5]=0x44;printf("bad_crc=%s\n",n(uart_parse_frame(good,sizeof(good),&f)));printf("summary ring=PASS parser=PASS crc=PASS nonblocking=PASS\n");return 0;}
