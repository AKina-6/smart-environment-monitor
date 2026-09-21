#include <assert.h>
#include "rtos/isr_sync.h"
int main(void){critical_section_t c;critical_init(&c);critical_enter(&c);assert(!c.interrupts_enabled&&c.nesting==1);critical_enter(&c);critical_exit(&c);assert(c.nesting==1&&!c.interrupts_enabled);critical_exit(&c);assert(c.nesting==0&&c.interrupts_enabled);deferred_queue_t q;uint32_t e;assert(deferred_init(&q));assert(deferred_post_from_isr(&q,0x10));assert(deferred_post_from_isr(&q,0x20));assert(deferred_get(&q,&e)&&e==0x10);assert(deferred_get(&q,&e)&&e==0x20);return 0;}
