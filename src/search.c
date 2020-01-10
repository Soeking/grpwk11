#define maxOf(a, b) a > b ? a : b

__attribute__((nonnull))void tableInit(int *table, const char *pattern, int ptnLen) {
    int cnt = 0;

    for (cnt = 97; cnt < 101; cnt++) {
        table[cnt] = ptnLen;
    }

    for (cnt = 0; cnt < ptnLen; cnt++) {
        table[(int) pattern[cnt]] = ptnLen - cnt - 1;
    }
}

__attribute__((nonnull))int bm(const char *text, const char *pattern, const int table[], int i, int txtLen, int ptnLen) {
    int j = ptnLen - 1;
    int lenMinus = ptnLen - 1;

    while ((i < txtLen) && (j >= 0)) {
        if (text[i] != pattern[j] && text[i] != 'x') {
            i += maxOf(table[(int) text[i]], ptnLen - j);
            j = lenMinus;
        } else {
            j--;
            i--;
        }
    }

    if (j < 0) return ++i;
    return -1;
}
