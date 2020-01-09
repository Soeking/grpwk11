#ifndef GRPWK11_PROCESSING_H
#define GRPWK11_PROCESSING_H

typedef struct {
    char *s;
    ushort len;
    int id;
    int table[101];
} str;

void proc(char *, str *, int, FILE *);

#endif