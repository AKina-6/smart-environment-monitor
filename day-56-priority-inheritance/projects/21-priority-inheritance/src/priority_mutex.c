#include "rtos/priority_mutex.h"
void task_init(task_t*t,const char*n,int p){if(t){t->name=n;t->base_priority=p;t->effective_priority=p;}}
void mutex_init(priority_mutex_t*m,bool e){if(m){m->locked=false;m->owner=0;m->inheritance_enabled=e;}}
bool mutex_lock(priority_mutex_t*m,task_t*t,task_t*w){if(!m||!t)return false;if(!m->locked){m->locked=true;m->owner=t;return true;}if(m->owner==t)return false;if(m->inheritance_enabled&&w&&w->effective_priority>m->owner->effective_priority)m->owner->effective_priority=w->effective_priority;return false;}
bool mutex_unlock(priority_mutex_t*m,task_t*t){if(!m||!m->locked||m->owner!=t)return false;t->effective_priority=t->base_priority;m->owner=0;m->locked=false;return true;}
