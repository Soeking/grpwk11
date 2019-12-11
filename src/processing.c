#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <bits/types/FILE.h>
#include "processing.h"
#include "strings.h"
#include "search.h"


void put(char *text, bool *used, char *string, int id) {
    int l = (int) strlen(string);
    for (int i = 0; i < l; ++i) {
        text[i + id] = string[i];
        used[i + id] = true;
    }
}

void proc(char *text, str *strs, int size, FILE *out) {
    int l = (int) strlen(text);
    char *outText;
    outText = (char *) malloc(sizeof(char) * 400002);
    strcpy(outText, text);
    bool *used;
    used = (bool *) malloc(sizeof(bool) * (size_t) l);
    for (int i = 0; i < size; ++i) {
        if (strs[i].len < 7) break;
        int index = 0;
        while (true) {
            index = bm(text, strs[i].s, index + strs[i].len);
            if (index < 0) break;
            if (strs[i].s[0] == 'c' && outText[index - 1] == 'd') continue;
            if (!used[index] && !used[index + strs[i].len - 1]) break;
        }
        if (index >= 0) {
            strs[i].id = index;
            put(outText, used, strs[i].s, strs[i].id);
        }
    }

//    for (int i = 0; i < l; ++i) {
//        if (outText[i] == 'x') fprintf(out, "a");
//        else fprintf(out, "%c", outText[i]);
//    }
    fprintf(out, "%s\n",outText);
}
