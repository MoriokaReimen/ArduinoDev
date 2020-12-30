#pragma once
#include <inttypes.h>

using CRC32 = uint32_t;

struct Packet
{
    int32_t start; /*0xAAAAAAAA*/
    int32_t data1;
    int32_t data2;
    int32_t end; /*0x55555555*/
    Packet() : start(0xAAAAAAAA), data1(0), end(0x55555555) {}
};

struct CRCPacket
{
    Packet packet;
    CRC32 crc;
};
