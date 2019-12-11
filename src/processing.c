#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <bits/types/FILE.h>
#include "processing.h"
#include "strings.h"
#include "search.h"

void proc(char *text, str *strs, bool *used, int size, FILE *out) {
    int l = (int) strlen(text);
    ushort m = strs[0].len;
    for (int i = 0; i < size; ++i) {
        if (strs[i].len < 70) break;
        int sub = bm(text, strs[i].s, 0);
        printf("%d ", sub);
    }
    printf("\n");
}