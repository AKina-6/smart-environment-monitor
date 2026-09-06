#include "config/crc32.h"
#include <stdint.h>

uint32_t crc32_ieee(const void *data, size_t length)
{
    const uint8_t *p = (const uint8_t *)data;
    uint32_t crc = 0xFFFFFFFFU;
    for (size_t i = 0U; i < length; ++i) {
        crc ^= p[i];
        for (uint8_t b = 0U; b < 8U; ++b) {
            const uint32_t mask = (uint32_t)-(int32_t)(crc & 1U);
            crc = (crc >> 1U) ^ (0xEDB88320U & mask);
        }
    }
    return ~crc;
}
