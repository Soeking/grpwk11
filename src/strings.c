#include <string.h>
#include <stdlib.h>

void append(char *base, char *parts) {
    int id = (int) strlen(base);
    int size = (int) strlen(parts);
    for (int i = 0; i < size; ++i) {
        base[i + id] = parts[i];
    }
    base[id + size] = '\0';
}