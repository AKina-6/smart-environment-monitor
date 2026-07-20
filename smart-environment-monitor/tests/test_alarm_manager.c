#include <assert.h>
#include <string.h>
#include "alarm_manager.h"
#include "telemetry.h"

static alarm_thresholds_t default_thresholds(void) {
    alarm_thresholds_t thresholds = {
        .temperature_high_c = 35.0F,
        .humidity_high_pct = 80.0F,
        .light_low_lux = 50.0F
    };
    return thresholds;
}

int main(void) {
    const alarm_thresholds_t thresholds = default_thresholds();

    environment_data_t normal = {25.0F, 60.0F, 300.0F, 1000U, true};
    assert(alarm_evaluate(&normal, &thresholds) == ALARM_NONE);

    environment_data_t hot = {36.0F, 60.0F, 300.0F, 1000U, true};
    assert(alarm_evaluate(&hot, &thresholds) == ALARM_TEMP_HIGH);

    environment_data_t multiple = {40.0F, 90.0F, 20.0F, 1000U, true};
    const uint32_t expected =
        ALARM_TEMP_HIGH | ALARM_HUMIDITY_HIGH | ALARM_LIGHT_LOW;
    assert(alarm_evaluate(&multiple, &thresholds) == expected);

    environment_data_t invalid = {0.0F, 0.0F, 0.0F, 1000U, false};
    assert(alarm_evaluate(&invalid, &thresholds) == ALARM_SENSOR_FAULT);

    char json[192];
    assert(telemetry_format_json(json, sizeof(json), &normal, 0U) > 0);
    assert(strstr(json, "\"temperature_c\":25.0") != 0);
    assert(strstr(json, "\"alarm_mask\":0") != 0);

    return 0;
}
