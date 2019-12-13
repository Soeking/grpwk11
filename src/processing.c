#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <bits/types/FILE.h>
#include "processing.h"
#include "strings.h"
#include "search.h"

void revert(const char *baseText, char *text, bool *used, int id, int l) {
    for (int i = 0; i < l; ++i) {
        if (baseText[i + id] == 'x') text[i + id] = 'x';
        used[i + id] = false;
    }
}

void put(char *text, bool *used, const char *string, int id, int l) {
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
    int fault = 0;
    for (int i = 0; i < size; ++i) {
        if (strs[i].len < 30) break;
        int index = strs[i].len - 1;
        while (true) {
            index = bm(text, strs[i].s, index);
            if (index < 0) {
//                int first = bm(bm(text, strs[i].s, index + strs[i].len);
//                revert(text, outText, used, strs[].id, strs[].len);
                fault++;
                break;
            }
            if ((strs[i].s[0] == 'c' && outText[index - 1] == 'd') ||
                (strs[i].s[strs[i].len - 1] == 'd' && outText[index + strs[i].len] == 'c'))
                goto CONT;
            if (!used[index] && !used[index + strs[i].len - 1]) break;
            CONT:;
            index += strs[i].len;
        }
        if (index >= 0) {
            strs[i].id = index;
            put(outText, used, strs[i].s, strs[i].id, strs[i].len);
        }
    }
    printf("fault: %d\n", fault);

//    for (int i = 0; i < l; ++i) {
//        if (outText[i] == 'x') fprintf(out, "a");
//        else fprintf(out, "%c", outText[i]);
//    }
    fprintf(out, "%s\n", outText);
}
