#include <assert.h>
#include <string.h>
#include "rtos/queue.h"
int main(){queue_t q;uint8_t out[32];uint32_t n;const uint8_t a[]="sensor",b[]="alarm";queue_init(&q);assert(queue_empty(&q));assert(queue_send(&q,a,6));assert(queue_send(&q,b,5));assert(queue_receive(&q,out,&n)&&n==6&&!memcmp(out,a,6));assert(queue_receive(&q,out,&n)&&n==5&&!memcmp(out,b,5));assert(queue_empty(&q));for(int i=0;i<QUEUE_CAPACITY;i++)assert(queue_send(&q,a,6));assert(queue_full(&q)&&!queue_send(&q,a,6));return 0;}
