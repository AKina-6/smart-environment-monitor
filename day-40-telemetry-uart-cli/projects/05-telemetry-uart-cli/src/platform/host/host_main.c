#include <stdio.h>
#include "cli/cli.h"

static void run(cli_context_t *ctx, const char *cmd)
{
    char out[256];
    cli_execute(ctx,cmd,out,sizeof(out));
    printf("> %s\n%s\n",cmd,out);
}

int main(void)
{
    runtime_config_t cfg; runtime_config_set_defaults(&cfg);
    telemetry_snapshot_t tel={24.8f,46.5f,380.0f,false,false,false,"NORMAL",12500U,1U};
    cli_context_t cli; cli_init(&cli,&cfg,&tel);
    run(&cli,"status");
    run(&cli,"get hot_on");
    run(&cli,"set hot_on 31.5");
    run(&cli,"get hot_on");
    run(&cli,"set hot_off 32.0");
    run(&cli,"set hold_ms 1500");
    run(&cli,"get hold_ms");
    run(&cli,"badcmd");
    printf("summary ok=%u error=%u updates=%u hot_on=%.1f hot_off=%.1f hold=%u\n",
        cli.commands_ok,cli.commands_error,cli.config_updates,
        cfg.hot_on_c,cfg.hot_off_c,cfg.min_hold_ms);
    return 0;
}
