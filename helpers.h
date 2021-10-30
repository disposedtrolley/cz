#ifndef HELPERS_H
#define HELPERS_H

typedef enum {
    ZRet_Success = 0,
    ZRet_IOReadError = 1
} ZRet;

ZRet read_story_file(char *path, uint8_t **buf, uint32_t *len);

void panic(const char *fmt, ...);

#endif