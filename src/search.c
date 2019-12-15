#include <stdlib.h>
#include <string.h>
#include "search.h"

void tableInit(int *table, const char *pattern, int ptnLen) {
    int cnt = 0;

    for (cnt = 0; cnt < 256; cnt++) {
        table[cnt] = ptnLen;
    }

    for (cnt = 0; cnt < ptnLen; cnt++) {
        table[(int) pattern[cnt]] = ptnLen - cnt - 1;
    }
}

int findNext(int *table, char target, int remain) {
    return table[(int) target] > remain ? table[(int) target] : remain;
}

int bm(const char *text, const char *pattern, int i, int txtLen, int ptnLen) {
    int table[256];
    int j = ptnLen - 1;

    tableInit(table, pattern, ptnLen);

    if (i == 0) i = ptnLen - 1;
    while ((i < txtLen) && (j >= 0)) {
        if (text[i] != pattern[j] && text[i] != 'x') {
            i += findNext(table, text[i], (ptnLen - j));
            j = ptnLen - 1;
        } else {
            j--;
            i--;
        }
    }

    if (j < 0) return ++i;
    return -1;
}
