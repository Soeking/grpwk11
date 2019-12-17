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
            return i;
        }
    }
    return -1;
}

int loopBm(char *text, str s, int l, int index) {
    while (true) {
        index = bm(text, s.s, s.table, index, l, s.len);
        if (index < 0) break;
        if ((s.s[0] == 'c' && text[index - 1] == 'd') ||
            (s.s[s.len - 1] == 'd' && text[index + s.len] == 'c'))
            index += s.len;
        else break;
    }
    return index;
}

void procStr(char *text, char *outText, bool *used, int i, str *strs, int l, int size) {
    int index = loopBm(text, strs[i], l, strs[i].len + strs[i].id);
    while (true) {
        if (index < 0) break;
        if (!used[index] && !used[index + strs[i].len - 1]) break;
        index = loopBm(text, strs[i], l, index + strs[i].len);
    }
    if (index < 0) {
        int first = loopBm(text, strs[i], l, strs[i].len + strs[i].id);
        if (first < 0) first = loopBm(text, strs[i], l, strs[i].len - 1); //多分あった方がいい(精度落ちたけど)
        int idf = searchId(strs, first, size);
        int idl = searchId(strs, first + strs[i].len - 1, size);
        if (idf > 0) revert(text, outText, used, strs[idf].id, strs[idf].len);
        if (idl > 0 && idf != idl) revert(text, outText, used, strs[idl].id, strs[idl].len);
        strs[i].id = first;
        put(outText, used, strs[i].s, strs[i].id, strs[i].len);
        if (first < 0) printf("min\n");
        if (idf > 0) {
            if (i != idf)
                procStr(text, outText, used, idf, strs, l, size);
        }
        if (idl > 0 && idf != idl) {
            if (i != idl)
                procStr(text, outText, used, idl, strs, l, size);
        }
    } else {
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
        if (strs[i].len < 20) break;
        tableInit(strs[i].table, strs[i].s, strs[i].len);
        procStr(text, outText, used, i, strs, l, size);
    }

//    for (int i = 0; i < l; ++i) {
//        if (outText[i] == 'x') fprintf(out, "a");
//        else fprintf(out, "%c", outText[i]);
//    }
    fprintf(out, "%s\n", outText);
}
