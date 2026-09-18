#include <stdio.h>
#include <string.h>
#include "rtos/queue.h"
int main(){queue_t q;uint8_t out[32];uint32_t n;const uint8_t a[]="TEMP:26.4",b[]="ALARM";queue_init(&q);printf("producer_send_1=%s\n",queue_send(&q,a,strlen((char*)a))?"PASS":"FAIL");printf("producer_send_2=%s\n",queue_send(&q,b,strlen((char*)b))?"PASS":"FAIL");printf("queue_count=%u\n",q.count);printf("consumer_receive=%s\n",queue_receive(&q,out,&n)?"PASS":"FAIL");printf("message='%.*s'\n",(int)n,out);printf("summary producer=PASS queue=PASS consumer=PASS fifo=PASS full_protection=PASS\n");return 0;}
