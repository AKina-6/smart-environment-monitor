#ifndef PRIORITY_MUTEX_H
#define PRIORITY_MUTEX_H
#include <stdbool.h>
typedef struct task{const char*name;int base_priority;int effective_priority;}task_t;
typedef struct{bool locked;task_t*owner;bool inheritance_enabled;}priority_mutex_t;
void task_init(task_t*,const char*,int);void mutex_init(priority_mutex_t*,bool);
bool mutex_lock(priority_mutex_t*,task_t*,task_t*);bool mutex_unlock(priority_mutex_t*,task_t*);
#endif
