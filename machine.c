#include "machine.h"

#include <stdint.h>
#include <assert.h>
#include "memory.h"

struct config config = {
        .interpreter_number = 12,
        .interpreter_version = 0,
        .screen_width = 80,
        .screen_height = 24,
};

ZRet initialise_irom(uint8_t zversion) {
    // Screen dimensions
    if (zversion >= 4) {
        assert(memory_write_byte(0x1E, config.interpreter_number) == ZRet_Success);
        assert(memory_write_byte(0x1F, config.interpreter_version) == ZRet_Success);
        assert(memory_write_byte(0x20, config.screen_height) == ZRet_Success);
        assert(memory_write_byte(0x21, config.screen_width) == ZRet_Success);
    }

    if (zversion >= 5) {
        // The "units" measurement appears to exist for the purposes of
        // displaying pictures. We're not concerned about that now, so it's
        // probably safe to stick with the humble dimenions of 80x24.
        assert(memory_write_word(0x22, config.screen_width) == ZRet_Success);
        assert(memory_write_word(0x24, config.screen_height) == ZRet_Success);
    }

    return ZRet_Success;
}

ZRet start_game_loop(uint8_t zversion, uint8_t zversion_specific) {
    initialise_irom(zversion);
    return ZRet_Success;
}