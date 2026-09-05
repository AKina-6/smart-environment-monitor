#include "cli/cli.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int reply(char *out, size_t cap, const char *fmt, const char *name, double value)
{
    return snprintf(out, cap, fmt, name, value);
}

void cli_init(cli_context_t *ctx, runtime_config_t *config, telemetry_snapshot_t *telemetry)
{
    if (ctx == NULL) return;
    ctx->config = config;
    ctx->telemetry = telemetry;
    ctx->commands_ok = 0U;
    ctx->commands_error = 0U;
    ctx->config_updates = 0U;
}

static int do_get(cli_context_t *ctx, const char *name, char *out, size_t cap)
{
    const runtime_config_t *c = ctx->config;
    if (strcmp(name,"hot_on")==0) return reply(out,cap,"%s=%.1f",name,c->hot_on_c);
    if (strcmp(name,"hot_off")==0) return reply(out,cap,"%s=%.1f",name,c->hot_off_c);
    if (strcmp(name,"dark_on")==0) return reply(out,cap,"%s=%.1f",name,c->dark_on_lux);
    if (strcmp(name,"dark_off")==0) return reply(out,cap,"%s=%.1f",name,c->dark_off_lux);
    if (strcmp(name,"hold_ms")==0) return snprintf(out,cap,"hold_ms=%u",c->min_hold_ms);
    return snprintf(out,cap,"ERR unknown key");
}

static int do_set(cli_context_t *ctx, const char *name, const char *value, char *out, size_t cap)
{
    runtime_config_t next = *ctx->config;
    char *end = NULL;
    double v = strtod(value,&end);
    if (end == value || *end != '\0') return snprintf(out,cap,"ERR invalid value");
    if (strcmp(name,"hot_on")==0) next.hot_on_c=(float)v;
    else if (strcmp(name,"hot_off")==0) next.hot_off_c=(float)v;
    else if (strcmp(name,"dark_on")==0) next.dark_on_lux=(float)v;
    else if (strcmp(name,"dark_off")==0) next.dark_off_lux=(float)v;
    else if (strcmp(name,"hold_ms")==0) {
        if (v < 0.0 || v > 60000.0) return snprintf(out,cap,"ERR invalid value");
        next.min_hold_ms=(unsigned int)v;
    } else return snprintf(out,cap,"ERR unknown key");
    if (!runtime_config_is_valid(&next)) return snprintf(out,cap,"ERR config rejected");
    *ctx->config=next;
    ctx->config_updates++;
    return snprintf(out,cap,"OK %s=%s",name,value);
}

int cli_execute(cli_context_t *ctx, const char *line, char *out, size_t cap)
{
    if (ctx == NULL || line == NULL || out == NULL || cap == 0U) return -1;
    char copy[96];
    snprintf(copy,sizeof(copy),"%s",line);
    char *cmd=strtok(copy," \t\r\n");
    if (cmd == NULL) { ctx->commands_error++; return snprintf(out,cap,"ERR empty"); }
    int n=0; int ok=1;
    if (strcmp(cmd,"help")==0) {
        n=snprintf(out,cap,"help | status | get <key> | set <key> <value>");
    } else if (strcmp(cmd,"status")==0) {
        n=telemetry_format(ctx->telemetry,out,cap);
    } else if (strcmp(cmd,"get")==0) {
        char *name=strtok(NULL," \t\r\n");
        if (!name) { ok=0; n=snprintf(out,cap,"ERR usage: get <key>"); }
        else { n=do_get(ctx,name,out,cap); if (strncmp(out,"ERR",3)==0) ok=0; }
    } else if (strcmp(cmd,"set")==0) {
        char *name=strtok(NULL," \t\r\n"); char *value=strtok(NULL," \t\r\n");
        if (!name || !value) { ok=0; n=snprintf(out,cap,"ERR usage: set <key> <value>"); }
        else { n=do_set(ctx,name,value,out,cap); if (strncmp(out,"ERR",3)==0) ok=0; }
    } else { ok=0; n=snprintf(out,cap,"ERR unknown command"); }
    if (ok) ctx->commands_ok++; else ctx->commands_error++;
    return n;
}
