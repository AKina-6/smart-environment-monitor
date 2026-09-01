#include <assert.h>
#include "sensor/sensor_validation.h"

int main(void)
{
    assert(sensor_validate_temperature(25.0f) == SENSOR_HEALTH_OK);
    assert(sensor_validate_temperature(100.0f) == SENSOR_HEALTH_RANGE_ERROR);
    assert(sensor_validate_humidity(50.0f) == SENSOR_HEALTH_OK);
    assert(sensor_validate_humidity(120.0f) == SENSOR_HEALTH_RANGE_ERROR);
    assert(sensor_validate_light(1000.0f) == SENSOR_HEALTH_OK);
    assert(sensor_validate_light(-1.0f) == SENSOR_HEALTH_RANGE_ERROR);

    sensor_snapshot_t s = {
        .timestamp_ms = 1000U,
        .temp_health = SENSOR_HEALTH_OK,
        .humidity_health = SENSOR_HEALTH_OK,
        .light_health = SENSOR_HEALTH_OK
    };
    sensor_apply_stale_check(&s, 4000U, 2000U);
    assert(s.temp_health == SENSOR_HEALTH_STALE);
    assert(s.humidity_health == SENSOR_HEALTH_STALE);
    assert(s.light_health == SENSOR_HEALTH_STALE);
    return 0;
}
