#include "machine.h"

#include <stdint.h>
#include "memory.h"
#include "stack.h"

struct config config = {
        .interpreter_number = 12,
        .interpreter_version = 0,
        .screen_width = 80,
        .screen_height = 24,
};

ZRet initialise_irom(uint8_t zversion) {
    // Screen dimensions
    if (zversion >= 4) {
        memory_write_byte(0x1E, config.interpreter_number);
        memory_write_byte(0x1F, config.interpreter_version);
        memory_write_byte(0x20, config.screen_height);
        memory_write_byte(0x21, config.screen_width);
    }

    if (zversion >= 5) {
        // The "units" measurement appears to exist for the purposes of
        // displaying pictures. We're not concerned about that now, so it's
        // probably safe to stick with the humble dimenions of 80x24.
        memory_write_word(0x22, config.screen_width);
        memory_write_word(0x24, config.screen_height);
    }

    return ZRet_Success;
}

ZRet start_game_loop(uint8_t zversion, uint8_t zversion_specific) {
    // IROM
    initialise_irom(zversion);

    // Stack
    initialise_stack();
    push((Frame){.return_pc = memory_read_word(0x06)});

    return ZRet_Success;
}