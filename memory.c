#include <stdint.h>

#include "memory.h"
#include "helpers.h"

uint8_t *memory;
uint32_t memory_size;

ZRet memory_read_byte(uint32_t addr, uint8_t *result) {
    if (addr > memory_size) {
        return ZRet_MemoryReadError;
    }

    *result = memory[addr];

    return ZRet_Success;
}

ZRet memory_read_word(uint32_t addr, uint16_t *result) {
    if (addr > memory_size - 1) {
        return ZRet_MemoryReadError;
    }

    *result = memory[addr] << 8 | memory[addr + 1];

    return ZRet_Success;
}

ZRet memory_write_byte(uint32_t addr, uint8_t data) {
    if (addr > memory_size) {
        return ZRet_MemoryWriteError;
    }

    memory[addr] = data;

    return ZRet_Success;
}

ZRet memory_write_word(uint32_t addr, uint16_t data) {
    if (addr > memory_size - 1) {
        return ZRet_MemoryWriteError;
    }

    memory[addr] = data >> 8;
    memory[addr+1] = (uint8_t) data;

    return ZRet_Success;
}