#include "rtos/queue.h"
#include <string.h>
void queue_init(queue_t*q){if(q)*q=(queue_t){0};}
bool queue_empty(const queue_t*q){return !q||q->count==0;}
bool queue_full(const queue_t*q){return q&&q->count==QUEUE_CAPACITY;}
bool queue_send(queue_t*q,const uint8_t*d,uint32_t n){if(!q||!d||!n||n>MESSAGE_MAX||queue_full(q))return false;memcpy(q->items[q->head].data,d,n);q->items[q->head].length=n;q->head=(q->head+1)%QUEUE_CAPACITY;q->count++;return true;}
bool queue_receive(queue_t*q,uint8_t*d,uint32_t*n){if(!q||!d||!n||queue_empty(q))return false;uint32_t len=q->items[q->tail].length;memcpy(d,q->items[q->tail].data,len);*n=len;q->tail=(q->tail+1)%QUEUE_CAPACITY;q->count--;return true;}
