#include <stdint.h>
#include <assert.h>

#include "memory.h"

uint8_t *memory;
uint32_t memory_size;

uint8_t memory_read_byte(uint32_t addr) {
    assert(addr < memory_size);
    return memory[addr];
}

uint16_t memory_read_word(uint32_t addr) {
    assert(addr < memory_size-1);
    return memory[addr] << 8 | memory[addr + 1];
}

void memory_write_byte(uint32_t addr, uint8_t data) {
    assert(addr < memory_size);
    memory[addr] = data;
}

void memory_write_word(uint32_t addr, uint16_t data) {
    assert(addr < memory_size-1);
    memory[addr] = data >> 8;
    memory[addr+1] = (uint8_t) data;
}