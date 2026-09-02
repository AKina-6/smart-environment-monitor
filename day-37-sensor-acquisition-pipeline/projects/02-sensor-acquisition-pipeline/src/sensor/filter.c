#include "sensor/filter.h"
#include <stddef.h>
void moving_average_init(moving_average_t *f){ if(!f) return; f->count=0; f->index=0; f->sum=0.0f; for(size_t i=0;i<8;i++) f->buffer[i]=0.0f; }
float moving_average_update(moving_average_t *f,float s){ if(!f) return s; if(f->count<8){ f->buffer[f->index]=s; f->sum+=s; f->count++; f->index=(f->index+1U)%8U; } else { f->sum-=f->buffer[f->index]; f->buffer[f->index]=s; f->sum+=s; f->index=(f->index+1U)%8U; } return f->sum/(float)f->count; }
void ema_filter_init(ema_filter_t *f,float a){ if(!f) return; if(a<0.0f) a=0.0f; if(a>1.0f) a=1.0f; f->initialized=false; f->alpha=a; f->value=0.0f; }
float ema_filter_update(ema_filter_t *f,float s){ if(!f) return s; if(!f->initialized){ f->value=s; f->initialized=true; } else f->value=f->alpha*s+(1.0f-f->alpha)*f->value; return f->value; }
