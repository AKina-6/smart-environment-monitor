#include "rtos/isr_sync.h"
void critical_init(critical_section_t*c){if(c){c->nesting=0;c->interrupts_enabled=true;}}
void critical_enter(critical_section_t*c){if(c){c->nesting++;c->interrupts_enabled=false;}}
void critical_exit(critical_section_t*c){if(c&&c->nesting){if(--c->nesting==0)c->interrupts_enabled=true;}}
bool deferred_init(deferred_queue_t*q){if(!q)return false;q->head=q->tail=q->count=0;return true;}
bool deferred_post_from_isr(deferred_queue_t*q,uint32_t e){if(!q||q->count==DEFERRED_QUEUE_SIZE)return false;q->events[q->head]=e;q->head=(q->head+1)%DEFERRED_QUEUE_SIZE;q->count++;return true;}
bool deferred_get(deferred_queue_t*q,uint32_t*e){if(!q||!e||q->count==0)return false;*e=q->events[q->tail];q->tail=(q->tail+1)%DEFERRED_QUEUE_SIZE;q->count--;return true;}
