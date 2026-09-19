#include <assert.h>
#include "rtos/event_timer.h"
int main(){event_group_t g;software_timer_t t;event_init(&g);assert(!event_wait_any(&g,3));event_set(&g,1);assert(event_wait_any(&g,3));assert(!event_wait_all(&g,3));event_set(&g,2);assert(event_wait_all(&g,3));event_clear(&g,1);assert(!event_wait_all(&g,3));timer_start(&t,1000,true);assert(!timer_tick(&t,400));assert(timer_tick(&t,600));assert(t.active);timer_start(&t,500,false);assert(timer_tick(&t,500));assert(!t.active);return 0;}
