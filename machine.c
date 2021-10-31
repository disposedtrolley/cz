#include "machine.h"

#include <stdint.h>
#include <stdlib.h>
#include <assert.h>

uint8_t memory_read_byte(Machine *m, uint32_t addr) {
    assert(addr < m->memory_size);
    return m->memory[addr];
}

uint16_t memory_read_word(Machine *m, uint32_t addr) {
    assert(addr < m->memory_size-1);
    return m->memory[addr] << 8 | m->memory[addr + 1];
}

void memory_write_byte(Machine *m, uint32_t addr, uint8_t data) {
    assert(addr < m->memory_size);
    m->memory[addr] = data;
}

void memory_write_word(Machine *m, uint32_t addr, uint16_t data) {
    assert(addr < m->memory_size-1);
    m->memory[addr] = data >> 8;
    m->memory[addr+1] = (uint8_t) data;
}

void initialise_stack(Machine *m) {
    // §6.3.3 of the spec provides two example stack sizes. We're using the
    // nfrotz stack size of 61440 bytes, which is 0x30 (sizeof Frame) * 0x500.
    m->stack = (Frame*)malloc(sizeof(Frame) * 0x500);
}

ZRet push(Machine *m, Frame f) {
    m->stack[m->sp] = f;
    m->sp++;

    return ZRet_Success;
}

ZRet initialise_irom(Machine *m, Config config, uint8_t zversion) {
    // Screen dimensions
    if (zversion >= 4) {
        memory_write_byte(m, 0x1E, config.interpreter_number);
        memory_write_byte(m, 0x1F, config.interpreter_version);
        memory_write_byte(m, 0x20, config.screen_height);
        memory_write_byte(m, 0x21, config.screen_width);
    }

    if (zversion >= 5) {
        // The "units" measurement appears to exist for the purposes of
        // displaying pictures. We're not concerned about that now, so it's
        // probably safe to stick with the humble dimenions of 80x24.
        memory_write_word(m, 0x22, config.screen_width);
        memory_write_word(m, 0x24, config.screen_height);
    }

    return ZRet_Success;
}

ZRet start_game_loop(Machine *m, Config config, uint8_t zversion, uint8_t zversion_specific) {
    // IROM
    initialise_irom(m, config, zversion);

    // Stack
    initialise_stack(m);
    push(m, (Frame){.return_pc = memory_read_word(m, 0x06)});

    return ZRet_Success;
}