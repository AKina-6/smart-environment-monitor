#include <stdio.h>
#include "control/actuator_policy.h"

static void run(actuator_state_t *s, const actuator_thresholds_t *c,
                system_health_t h, float t, float l, uint32_t now)
{
    actuator_policy_update(s,c,h,t,l,now);
    printf("t=%lu T=%.1f L=%.0f health=%u fan=%s light=%s alarm=%s blocked=%lu\n",
        (unsigned long)now,t,l,(unsigned)h,
        s->fan_on?"on":"off",s->light_on?"on":"off",s->alarm_on?"on":"off",
        (unsigned long)s->blocked_switch_count);
}

int main(void)
{
    actuator_thresholds_t cfg={30.0f,28.0f,100.0f,150.0f,1000U};
    actuator_state_t s;
    actuator_state_init(&s,0U);

    run(&s,&cfg,SYSTEM_NORMAL,29.0f,200.0f,0U);
    run(&s,&cfg,SYSTEM_NORMAL,30.5f,90.0f,500U);   /* blocked by hold */
    run(&s,&cfg,SYSTEM_NORMAL,30.5f,90.0f,1000U);  /* both can switch on */
    run(&s,&cfg,SYSTEM_NORMAL,29.2f,120.0f,1500U); /* hysteresis holds */
    run(&s,&cfg,SYSTEM_NORMAL,27.5f,160.0f,2000U); /* both off */
    run(&s,&cfg,SYSTEM_DEGRADED,31.0f,80.0f,3000U);/* warning alarm + outputs */
    run(&s,&cfg,SYSTEM_FAULT,40.0f,20.0f,3500U);   /* safe outputs */

    printf("summary fan_switches=%lu light_switches=%lu blocked=%lu alarm=%s\n",
        (unsigned long)s.fan_switch_count,
        (unsigned long)s.light_switch_count,
        (unsigned long)s.blocked_switch_count,
        s.alarm_on?"on":"off");
    return 0;
}
