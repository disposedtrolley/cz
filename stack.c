#include "stack.h"

#include <stdlib.h>

#include "helpers.h"

// While the spec makes a distinction between a call and routine stack, they
// can be implemented using the same structure.
Frame *stack;
uint16_t sp;

void initialise_stack() {
    // §6.3.3 of the spec provides two example stack sizes. We're using the
    // nfrotz stack size of 61440 bytes, which is 0x30 (sizeof Frame) * 0x500.
    stack = (Frame*)malloc(sizeof(Frame) * 0x500);
}

ZRet push(Frame f) {
    stack[sp] = f;
    sp++;

    return ZRet_Success;
}