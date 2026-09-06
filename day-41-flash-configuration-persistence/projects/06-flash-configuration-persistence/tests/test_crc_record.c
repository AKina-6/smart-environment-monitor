#include <assert.h>
#include <string.h>
#include "config/crc32.h"
#include "config/config_record.h"

int main(void)
{
    const char *s = "123456789";
    assert(crc32_ieee(s, strlen(s)) == 0xCBF43926U);

    runtime_config_t cfg;
    runtime_config_default(&cfg);
    config_record_t record;
    config_record_build(&record, &cfg, 7U);
    assert(config_record_validate(&record));
    record.crc32 ^= 1U;
    assert(!config_record_validate(&record));
    return 0;
}
