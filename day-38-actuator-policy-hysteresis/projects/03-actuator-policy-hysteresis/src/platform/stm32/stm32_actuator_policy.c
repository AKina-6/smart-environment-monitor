/* STM32 integration sketch: policy output -> GPIO/PWM/Buzzer BSP. */
#include "control/actuator_policy.h"
#include "stm32f1xx_hal.h"

extern void board_set_fan(bool on);
extern void board_set_light(bool on);
extern void board_set_alarm(bool on);

void actuator_apply_to_board(const actuator_state_t *state)
{
    if (!state) return;
    board_set_fan(state->fan_on);
    board_set_light(state->light_on);
    board_set_alarm(state->alarm_on);
}
