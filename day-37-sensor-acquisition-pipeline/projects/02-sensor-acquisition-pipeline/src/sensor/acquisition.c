#include "sensor/acquisition.h"
#include <stddef.h>
static bool due(uint32_t now,uint32_t next){ return (int32_t)(now-next)>=0; }
bool acquisition_pipeline_init(acquisition_pipeline_t *p,const sensor_source_t *s,uint32_t now){
 if(!p||!s||!s->read_temperature||!s->read_humidity||!s->read_light) return false;
 p->source=*s; moving_average_init(&p->temperature_ma); moving_average_init(&p->humidity_ma); ema_filter_init(&p->light_ema,0.25f);
 p->latest=(sensor_snapshot_t){0}; p->temperature_period_ms=1000U; p->humidity_period_ms=1000U; p->light_period_ms=250U;
 p->next_temperature_ms=now; p->next_humidity_ms=now; p->next_light_ms=now; p->coherence_window_ms=1000U;
 p->temperature_reads=p->humidity_reads=p->light_reads=p->read_failures=0U; return true;
}
void acquisition_pipeline_poll(acquisition_pipeline_t *p,uint32_t now){
 if(!p) return;
 float v;
 if(due(now,p->next_temperature_ms)){ p->next_temperature_ms+=p->temperature_period_ms; if(p->source.read_temperature(p->source.context,&v)){ p->latest.temperature_c=moving_average_update(&p->temperature_ma,v); p->latest.temperature_ms=now; p->latest.temperature_valid=true; p->temperature_reads++; } else { p->latest.temperature_valid=false; p->read_failures++; }}
 if(due(now,p->next_humidity_ms)){ p->next_humidity_ms+=p->humidity_period_ms; if(p->source.read_humidity(p->source.context,&v)){ p->latest.humidity_pct=moving_average_update(&p->humidity_ma,v); p->latest.humidity_ms=now; p->latest.humidity_valid=true; p->humidity_reads++; } else { p->latest.humidity_valid=false; p->read_failures++; }}
 if(due(now,p->next_light_ms)){ p->next_light_ms+=p->light_period_ms; if(p->source.read_light(p->source.context,&v)){ p->latest.light_lux=ema_filter_update(&p->light_ema,v); p->latest.light_ms=now; p->latest.light_valid=true; p->light_reads++; } else { p->latest.light_valid=false; p->read_failures++; }}
}
sensor_snapshot_t acquisition_pipeline_snapshot(acquisition_pipeline_t *p,uint32_t now){
 sensor_snapshot_t s={0}; if(!p) return s; s=p->latest; s.snapshot_ms=now;
 if(s.temperature_valid&&s.humidity_valid&&s.light_valid){ uint32_t min=s.temperature_ms,max=s.temperature_ms; if(s.humidity_ms<min)min=s.humidity_ms; if(s.light_ms<min)min=s.light_ms; if(s.humidity_ms>max)max=s.humidity_ms; if(s.light_ms>max)max=s.light_ms; s.coherent=(uint32_t)(max-min)<=p->coherence_window_ms; } else s.coherent=false;
 p->latest.coherent=s.coherent; p->latest.snapshot_ms=now; return s;
}
