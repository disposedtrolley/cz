#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

#include "helpers.h"

ZRet read_story_file(char *path, uint8_t **buf, uint32_t *len) {
    if (stat(path, &(struct stat){}) != 0) {
        return ZRet_IOReadError;
    }

    FILE *story_file = fopen(path, "r");

    fseek(story_file, 0, SEEK_END);
    long story_file_size = ftell(story_file);
    fseek(story_file, 0, SEEK_SET);

    *len = story_file_size;
    *buf = malloc(story_file_size + 1);

    fread(*buf, 1, story_file_size, story_file);
    fclose(story_file);

    return ZRet_Success;
}

void panic(const char *fmt, ...) {
    va_list ap;
    char str[1024];

    va_start(ap, fmt);
    vsnprintf(str, sizeof str, fmt, ap);
    va_end(ap);

    printf("Fatal error: %s", str);

    exit(EXIT_FAILURE);
}