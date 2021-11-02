#ifndef MACHINE_H
#define MACHINE_H

#include "helpers.h"

#include <stdbool.h>
#include <stdint.h>

typedef struct Frame {
    uint32_t return_pc;
    uint8_t flags;
    uint8_t result;
    uint8_t args;
    uint16_t locals[15];
    uint16_t n;
    uint16_t *routine_stack;
} Frame;

typedef struct Machine {
    uint8_t *memory;
    uint32_t memory_size;

    Frame *stack;
    uint16_t sp;
    uint16_t pc;
} Machine;

typedef struct Config {
    uint8_t interpreter_number;
    unsigned char interpreter_version;
    uint8_t screen_height;
    uint8_t screen_width;
    uint8_t default_bg_colour;
    uint8_t default_fg_colour;
    char *player_name;
} Config;

ZRet start_game_loop(Machine *m, Config config, uint8_t zversion, uint8_t zversion_specific);
uint8_t memory_read_byte(Machine *m, uint32_t addr);

#endif