#ifndef ISR_SYNC_H
#define ISR_SYNC_H
#include <stdbool.h>
#include <stdint.h>
#define DEFERRED_QUEUE_SIZE 8
typedef struct{uint32_t nesting;bool interrupts_enabled;}critical_section_t;
typedef struct{uint32_t events[DEFERRED_QUEUE_SIZE],head,tail,count;}deferred_queue_t;
void critical_init(critical_section_t*);void critical_enter(critical_section_t*);void critical_exit(critical_section_t*);
bool deferred_init(deferred_queue_t*);bool deferred_post_from_isr(deferred_queue_t*,uint32_t);bool deferred_get(deferred_queue_t*,uint32_t*);
#endif
