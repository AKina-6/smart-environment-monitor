#include "uart/uart_protocol.h"
void uart_ring_init(uart_ring_t*r){if(r)*r=(uart_ring_t){0};}
bool uart_ring_push(uart_ring_t*r,uint8_t v){if(!r||r->head-r->tail>=UART_RING_SIZE)return false;r->data[r->head%UART_RING_SIZE]=v;r->head++;return true;}
bool uart_ring_pop(uart_ring_t*r,uint8_t*v){if(!r||!v||r->head==r->tail)return false;*v=r->data[r->tail%UART_RING_SIZE];r->tail++;return true;}
uint8_t uart_crc8(const uint8_t*d,uint32_t n){uint8_t c=0;for(uint32_t i=0;i<n;i++)c^=d[i];return c;}
uart_status_t uart_parse_frame(const uint8_t*d,uint32_t n,uart_frame_t*f){
 if(!d||!f||n<4||d[0]!=0xAA)return UART_ERR_FORMAT;
 if(d[2]>UART_MAX_PAYLOAD)return UART_ERR_LENGTH;
 if(n!=(uint32_t)d[2]+4)return UART_ERR_LENGTH;
 f->type=d[1];f->length=d[2];
 for(uint32_t i=0;i<f->length;i++)f->payload[i]=d[3+i];
 f->crc=d[n-1];
 return uart_crc8(d+1,n-2)==f->crc?UART_OK:UART_ERR_CRC;
}
