#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#include "helpers.h"

uint8_t *memory;
uint32_t memory_size;

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

    return EXIT_SUCCESS;
}
