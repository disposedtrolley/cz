#ifndef MEMORY_H
#define MEMORY_H

#include <stdint.h>

#include "helpers.h"

extern uint8_t *memory;
extern uint32_t memory_size;

ZRet memory_read_byte(uint32_t addr, uint8_t *result);
ZRet memory_read_word(uint32_t addr, uint16_t *result);

ZRet memory_write_byte(uint32_t addr, uint8_t data);
ZRet memory_write_word(uint32_t addr, uint16_t data);

#endif