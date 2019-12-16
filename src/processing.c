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

int searchId(str *ss, int id, int size) {
    for (int i = 0; i < size; ++i) {
        if (ss[i].id <= id && id < (ss[i].id + ss[i].len)) {
            printf("ok\n");
            return i;
        }
    }
    printf("f\n");
    return -1;
}

void procStr(char *text, char *outText, bool *used, int i, str *strs, int l) {
    int index = strs[i].len - 1;
    while (true) {
        index = bm(text, strs[i].s, index, l, strs[i].len);
        if (index < 0) {
            int first = bm(text, strs[i].s, strs[i].len - 1, l, strs[i].len);
            int idf = searchId(strs, first, i);
            if (idf > 0) revert(text, outText, used, strs[idf].id, strs[idf].len);
            int idl = searchId(strs, first + strs[i].len - 1, i);
            if (idl > 0) revert(text, outText, used, strs[idl].id, strs[idl].len);
            procStr(text, outText, used, i, strs, l);
            //goto RES;
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

void proc(char *text, str *strs, int size, FILE *out) {
    int l = (int) strlen(text);
    char *outText;
    outText = (char *) malloc(sizeof(char) * 400002);
    strcpy(outText, text);
    bool *used;
    used = (bool *) malloc(sizeof(bool) * (size_t) l);
    memset(used, false, (size_t) l);
    for (int i = 0; i < size; ++i) {
        if (strs[i].len < 30) break;
        procStr(text, outText, used, i, strs, l);
    }

//    for (int i = 0; i < l; ++i) {
//        if (outText[i] == 'x') fprintf(out, "a");
//        else fprintf(out, "%c", outText[i]);
//    }
    fprintf(out, "%s\n", outText);
}
