#include <stdbool.h>

#ifndef GRPWK11_PROCESSING_H
#define GRPWK11_PROCESSING_H

typedef struct {
    char *s;
    ushort len;
    int id;
} str;

void proc(char *, str *, int, FILE *);

#endif