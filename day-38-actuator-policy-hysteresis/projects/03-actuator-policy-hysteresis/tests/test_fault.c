#include <assert.h>
#include "control/actuator_policy.h"

int main(void)
{
    actuator_thresholds_t c={30.0f,28.0f,100.0f,150.0f,0U};
    actuator_state_t s;
    actuator_state_init(&s,0U);
    actuator_policy_update(&s,&c,SYSTEM_NORMAL,35.0f,50.0f,0U);
    assert(s.fan_on && s.light_on);
    actuator_policy_update(&s,&c,SYSTEM_FAULT,35.0f,50.0f,10U);
    assert(!s.fan_on && !s.light_on && s.alarm_on);
    return 0;
}
