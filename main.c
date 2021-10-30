#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

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
    ret = memory_read_word(0x00, &result);
    if (ret != ZRet_Success) {
        panic("Could not read word");
    }

    printf("Word at 0x00: %#06hx", result);

    return EXIT_SUCCESS;
}
