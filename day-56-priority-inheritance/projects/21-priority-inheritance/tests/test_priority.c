#include <assert.h>
#include "rtos/priority_mutex.h"
int main(void){task_t l,h;task_init(&l,"low",1);task_init(&h,"high",10);priority_mutex_t a,b;mutex_init(&a,false);mutex_init(&b,true);assert(mutex_lock(&a,&l,0));assert(!mutex_lock(&a,&h,&h));assert(l.effective_priority==1);assert(mutex_unlock(&a,&l));assert(mutex_lock(&b,&l,0));assert(!mutex_lock(&b,&h,&h));assert(l.effective_priority==10);assert(mutex_unlock(&b,&l));assert(l.effective_priority==1);return 0;}
