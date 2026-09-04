#include <assert.h>
#include "ui/ui_model.h"

int main(void)
{
    ui_state_t state;
    ui_state_init(&state);

    assert(state.page == UI_PAGE_OVERVIEW);

    ui_next_page(&state);
    assert(state.page == UI_PAGE_SENSOR);

    ui_next_page(&state);
    assert(state.page == UI_PAGE_SYSTEM);

    ui_next_page(&state);
    assert(state.page == UI_PAGE_OVERVIEW);

    ui_previous_page(&state);
    assert(state.page == UI_PAGE_SYSTEM);

    ui_apply_health(&state, UI_HEALTH_FAULT);
    assert(state.page == UI_PAGE_FAULT);
    assert(state.forced_fault_entries == 1U);

    ui_next_page(&state);
    assert(state.page == UI_PAGE_FAULT);

    ui_apply_health(&state, UI_HEALTH_NORMAL);
    assert(state.page == UI_PAGE_SYSTEM);

    return 0;
}
