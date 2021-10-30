#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include "helpers.h"

uint8_t *memory;
uint32_t memory_size;
uint8_t zversion, zversion_specific;

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

int main(int argc, char *argv[]) {
    if (argc != 2) {
        panic("Expected one argument (path to story file), but got %d\n", argc);
    }

    char *story_file_path = argv[1];
    ZRet ret = read_story_file(story_file_path, &memory, &memory_size);
    if (ret != ZRet_Success) {
        panic("Could not read story file at '%s'", story_file_path);
    }

    printf("Length of story file: %d\n", memory_size);

    uint16_t result;
    assert(memory_read_word(0x00, &result) == ZRet_Success);

    assert(memory_write_byte(0x00, 0x08) == ZRet_Success);
    assert(memory_write_word(0x01, 0x0200) == ZRet_Success);

    assert(memory_read_byte(0x00, &zversion) == ZRet_Success);

    zversion_specific = zversion;

    if (zversion == 7 || zversion == 8) {
        // 7 and 8 are similar to 5, and it's easier to handle less cases.
        zversion = 5;
    }

    printf("Version: %d Version specific: %d\n", zversion, zversion_specific);

    return EXIT_SUCCESS;
}
