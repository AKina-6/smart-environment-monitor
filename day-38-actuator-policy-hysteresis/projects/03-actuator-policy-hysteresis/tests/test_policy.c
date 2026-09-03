#include <assert.h>
#include "control/actuator_policy.h"

int main(void)
{
    actuator_thresholds_t c={30.0f,28.0f,100.0f,150.0f,1000U};
    actuator_state_t s;
    actuator_state_init(&s,0U);

    actuator_policy_update(&s,&c,SYSTEM_NORMAL,30.5f,90.0f,500U);
    assert(!s.fan_on && !s.light_on);
    assert(s.blocked_switch_count==2U);

    actuator_policy_update(&s,&c,SYSTEM_NORMAL,30.5f,90.0f,1000U);
    assert(s.fan_on && s.light_on);

    actuator_policy_update(&s,&c,SYSTEM_NORMAL,29.0f,120.0f,1500U);
    assert(s.fan_on && s.light_on); /* inside hysteresis band */

    actuator_policy_update(&s,&c,SYSTEM_NORMAL,27.0f,170.0f,2000U);
    assert(!s.fan_on && !s.light_on);
    return 0;
}
