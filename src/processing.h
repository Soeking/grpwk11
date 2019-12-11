#include <stdbool.h>

#ifndef GRPWK11_PROCESSING_H
#define GRPWK11_PROCESSING_H

typedef struct {
    char *s;
    ushort len;
    bool use;
} str;

void proc(char *, str *, bool *, int, FILE *);

#endif