#ifndef UI_RENDERER_H
#define UI_RENDERER_H

#include <stddef.h>
#include "ui/ui_model.h"

#define UI_TEXT_BUFFER_SIZE 512U

size_t ui_render_text(
    const ui_state_t *state,
    const ui_data_t *data,
    char *output,
    size_t capacity
);

#endif
