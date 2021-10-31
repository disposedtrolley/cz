#ifndef STACK_H
#define STACK_H

#include <stdint.h>

#include "helpers.h"

// Following the Quetzel save file format to represent the call stack:
// https://www.inform-fiction.org/zmachine/standards/quetzal/
//
// The first few sections specify a compression scheme for the "massive" 65KB
// of dynamic memory that needs to be persisted. Let's not worry about that for
// now.

typedef struct Chunk {
    char *id;
    uint32_t len;
    uint8_t *data;
} Chunk;

typedef struct Frame {
    uint32_t return_pc;
    uint8_t flags;
    uint8_t result;
    uint8_t args;
    uint16_t locals[15];
    uint16_t n;
    uint16_t *routine_stack;
} Frame;

void initialise_stack();

ZRet push(Frame f);

#endif