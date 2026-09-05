#ifndef CLI_H
#define CLI_H
#include <stddef.h>
#include "cli/runtime_config.h"
#include "cli/telemetry.h"

typedef struct {
    runtime_config_t *config;
    telemetry_snapshot_t *telemetry;
    unsigned int commands_ok;
    unsigned int commands_error;
    unsigned int config_updates;
} cli_context_t;

void cli_init(cli_context_t *ctx, runtime_config_t *config, telemetry_snapshot_t *telemetry);
int cli_execute(cli_context_t *ctx, const char *line, char *out, size_t capacity);
#endif
