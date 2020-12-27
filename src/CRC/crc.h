# pragma once
#include <stddef.h>
#include <inttypes.h>

typedef uint8_t         CRC8;
typedef uint32_t        CRC32;

CRC8 calc_crc8(const void* src, const size_t size);
CRC32 calc_crc32(const void* src, const size_t size);
