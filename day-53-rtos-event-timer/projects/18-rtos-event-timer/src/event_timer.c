#include "rtos/event_timer.h"
void event_init(event_group_t*g){if(g)g->bits=0;}
void event_set(event_group_t*g,uint32_t b){if(g)g->bits|=b;}
void event_clear(event_group_t*g,uint32_t b){if(g)g->bits&=~b;}
bool event_wait_all(event_group_t*g,uint32_t b){return g&&(g->bits&b)==b;}
bool event_wait_any(event_group_t*g,uint32_t b){return g&&(g->bits&b)!=0;}
void timer_start(software_timer_t*t,uint32_t p,bool a){if(t){t->period_ms=p;t->elapsed_ms=0;t->active=p>0;t->auto_reload=a;}}
void timer_stop(software_timer_t*t){if(t)t->active=false;}
bool timer_tick(software_timer_t*t,uint32_t ms){if(!t||!t->active||!t->period_ms)return false;t->elapsed_ms+=ms;if(t->elapsed_ms<t->period_ms)return false;if(t->auto_reload)t->elapsed_ms%=t->period_ms;else t->active=false;return true;}
