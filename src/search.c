#include <stdlib.h>
#include <string.h>
#include "search.h"

void tableInit(int *table, const char *pattern, int ptn_len) {
    int cnt = 0;

    for (cnt = 97; cnt < 101; cnt++) {
        table[cnt] = ptn_len;
    }

    for (cnt = 0; cnt < ptn_len; cnt++) {
        table[(int) pattern[cnt]] = ptn_len - cnt - 1;
    }
}

int findNext(int *table, char target, int remain) {
    return table[(int) target] > remain ? table[(int) target] : remain;
}

int bm(const char *text, const char *pattern, int i, int txtLen, int ptnLen) {
    int table[102];
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
