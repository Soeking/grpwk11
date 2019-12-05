#include <stdio.h>
#include <stdlib.h>
#include "read.h"

void readFile(FILE *input, char *t, char **s, int *x) {
    fgets(t, 400002, input);
    int i = 0;
    while (fscanf(input, "%s\n", s[i]) != EOF) {
        i++;
    }
    *x = i;
}
