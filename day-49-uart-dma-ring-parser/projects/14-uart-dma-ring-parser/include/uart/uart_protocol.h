#ifndef UART_PROTOCOL_H
#define UART_PROTOCOL_H
#include <stdbool.h>
#include <stdint.h>
#define UART_RING_SIZE 64
#define UART_MAX_PAYLOAD 32
typedef enum { UART_OK=0, UART_ERR_FORMAT, UART_ERR_LENGTH, UART_ERR_CRC } uart_status_t;
typedef struct { uint8_t data[UART_RING_SIZE]; uint32_t head,tail; } uart_ring_t;
typedef struct { uint8_t type,length,payload[UART_MAX_PAYLOAD],crc; } uart_frame_t;
void uart_ring_init(uart_ring_t*);
bool uart_ring_push(uart_ring_t*,uint8_t);
bool uart_ring_pop(uart_ring_t*,uint8_t*);
uint8_t uart_crc8(const uint8_t*,uint32_t);
uart_status_t uart_parse_frame(const uint8_t*,uint32_t,uart_frame_t*);
#endif
