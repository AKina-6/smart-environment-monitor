#ifndef RTOS_QUEUE_H
#define RTOS_QUEUE_H
#include <stdbool.h>
#include <stdint.h>
#define QUEUE_CAPACITY 8
#define MESSAGE_MAX 32
typedef struct { uint8_t data[MESSAGE_MAX]; uint32_t length; } message_t;
typedef struct { message_t items[QUEUE_CAPACITY]; uint32_t head,tail,count; } queue_t;
void queue_init(queue_t*);
bool queue_send(queue_t*,const uint8_t*,uint32_t);
bool queue_receive(queue_t*,uint8_t*,uint32_t*);
bool queue_empty(const queue_t*);
bool queue_full(const queue_t*);
#endif
