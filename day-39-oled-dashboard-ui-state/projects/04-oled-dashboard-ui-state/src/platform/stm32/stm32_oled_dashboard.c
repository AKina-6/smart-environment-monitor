/*
 * STM32 + SSD1306 dashboard integration example.
 * Reuse the OLED driver from the earlier STM32 project.
 */
#include "ui/ui_model.h"
#include "ui/ui_renderer.h"
#include <stdint.h>
#include <string.h>

/* Replace with the actual SSD1306 functions already present in the repo. */
extern void ssd1306_clear(void);
extern void ssd1306_draw_text(uint8_t x, uint8_t y, const char *text);
extern void ssd1306_update(void);

static ui_state_t dashboard_state;

void dashboard_init(void)
{
    ui_state_init(&dashboard_state);
}

void dashboard_button_next(void)
{
    ui_next_page(&dashboard_state);
}

void dashboard_button_previous(void)
{
    ui_previous_page(&dashboard_state);
}

void dashboard_render(const ui_data_t *data)
{
    char buffer[UI_TEXT_BUFFER_SIZE];
    char *line;
    uint8_t y = 0U;

    if (data == 0) return;

    ui_apply_health(&dashboard_state, data->health);
    (void)ui_render_text(&dashboard_state, data, buffer, sizeof(buffer));

    ssd1306_clear();

    line = strtok(buffer, "\n");
    while (line != 0 && y < 64U) {
        ssd1306_draw_text(0U, y, line);
        y = (uint8_t)(y + 12U);
        line = strtok(0, "\n");
    }

    ssd1306_update();
}
