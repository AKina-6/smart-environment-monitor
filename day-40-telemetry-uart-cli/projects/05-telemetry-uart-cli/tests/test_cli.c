#include <assert.h>
#include <string.h>
#include "cli/cli.h"
int main(void){runtime_config_t c; runtime_config_set_defaults(&c); telemetry_snapshot_t t={25,50,300,false,false,false,"NORMAL",1000,0}; cli_context_t x; cli_init(&x,&c,&t); char out[256]; cli_execute(&x,"set hot_on 31.5",out,sizeof(out)); assert(c.hot_on_c>31.4f&&c.hot_on_c<31.6f); cli_execute(&x,"set hot_off 32",out,sizeof(out)); assert(strncmp(out,"ERR",3)==0); assert(c.hot_off_c==28.0f); cli_execute(&x,"status",out,sizeof(out)); assert(strstr(out,"HEALTH=NORMAL")!=0); assert(x.config_updates==1U); return 0;}
