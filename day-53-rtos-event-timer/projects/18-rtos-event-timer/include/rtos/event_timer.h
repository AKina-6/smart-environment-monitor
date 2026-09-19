#ifndef EVENT_TIMER_H
#define EVENT_TIMER_H
#include <stdbool.h>
#include <stdint.h>
typedef struct { uint32_t bits; } event_group_t;
typedef struct { uint32_t period_ms, elapsed_ms; bool active, auto_reload; } software_timer_t;
void event_init(event_group_t*);
void event_set(event_group_t*,uint32_t);
void event_clear(event_group_t*,uint32_t);
bool event_wait_all(event_group_t*,uint32_t);
bool event_wait_any(event_group_t*,uint32_t);
void timer_start(software_timer_t*,uint32_t,bool);
void timer_stop(software_timer_t*);
bool timer_tick(software_timer_t*,uint32_t);
#endif
