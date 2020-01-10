#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "processing.h"
#include "search.h"

__attribute__((nonnull))void revert(const char const *baseText, char *text, int *used, int id, int l) {
    for (int i = 0; i < l; ++i) {
        if (baseText[i + id] == 'x') text[i + id] = 'x';
        used[i + id] = -1;
    }
}

__attribute__((nonnull))void put(char *text, int *used, const char const *string, int id, int l, int strId) {
    for (int i = 0; i < l; ++i) {
        text[i + id] = string[i];
        used[i + id] = strId;
    }
}

__attribute__((nonnull))int searchId(const str const *ss, int id, int size) {
    for (int i = 0; i < size; ++i) {
        if (ss[i].id <= id && id < (ss[i].id + ss[i].len)) {
            return i;
        }
    }
    return -1;
}

__attribute__((nonnull))int loopBm(const char const *text, const char const *outText, str s, int l, int index) {
    while (1) {
        index = bm(text, s.s, s.table, index, l, s.len);
        if (index < 0) break;
        if ((s.s[0] == 'c' && outText[index - 1] == 'd') ||
            (s.s[s.len - 1] == 'd' && outText[index + s.len] == 'c'))
            index += s.len;
        else break;
    }
    return index;
}

__attribute__((nonnull))int loopSoft(const char const *text, str s, int l, int index) {
    while (1) {
        index = bm(text, s.s, s.table, index, l, s.len);
        if (index < 0) break;
        if ((s.s[0] == 'c' && text[index - 1] == 'd') ||
            (s.s[s.len - 1] == 'd' && text[index + s.len] == 'c'))
            index += s.len;
        else break;
    }
    return index;
}

__attribute__((nonnull))void procStr(const char const *text, char *outText, int *used, int i, str *strs, int l, int size) {
    int index = loopBm(text, outText, strs[i], l, strs[i].len + strs[i].id);
    while (1) {
        if (index < 0) break;
        if (used[index] < 0 && used[index + strs[i].len - 1] < 0) break;
        index = loopBm(text, outText, strs[i], l, index + strs[i].len);
    }
    if (index < 0) {
        int first = loopBm(text, outText, strs[i], l, strs[i].len + strs[i].id);
        if (first < 0) first = loopBm(text, outText, strs[i], l, strs[i].len - 1);
        if (first < 0) return;
        int idf = searchId(strs, first, size);
        int idl = searchId(strs, first + strs[i].len - 1, size);
        int fb = 0, lb = 0;
        if (idf > 0 && i != idf) {
            revert(text, outText, used, strs[idf].id, strs[idf].len);
            strs[idf].free = 1;
            fb = 1;
        }
        if (idl > 0 && idf != idl && i != idl) {
            revert(text, outText, used, strs[idl].id, strs[idl].len);
            strs[idl].free = 1;
            lb = 1;
        }

        strs[i].id = first;
        strs[i].free = 0;
        put(outText, used, strs[i].s, strs[i].id, strs[i].len, i);
        if (fb) procStr(text, outText, used, idf, strs, l, size);
        if (lb) procStr(text, outText, used, idl, strs, l, size);
    } else {
        strs[i].id = index;
        strs[i].free = 0;
        put(outText, used, strs[i].s, strs[i].id, strs[i].len, i);
    }
}

__attribute__((nonnull))void lastProc(const char const *text, char *outText, int *used, int i, str *strs, int l, int size) {
    int first = loopSoft(text, strs[i], l, strs[i].len + strs[i].id);
    if (first < 0) first = loopSoft(text, strs[i], l, strs[i].len - 1);
    int idf = searchId(strs, first, size);
    int idl = searchId(strs, first + strs[i].len - 1, size);
    int fb = 0, lb = 0;
    if (idf > 0 && i != idf) {
        revert(text, outText, used, strs[idf].id, strs[idf].len);
        strs[idf].free = 1;
        fb = 1;
    }
    if (idl > 0 && idf != idl && i != idl) {
        revert(text, outText, used, strs[idl].id, strs[idl].len);
        strs[idl].free = 1;
        lb = 1;
    }

    strs[i].id = first;
    strs[i].free = 0;
    put(outText, used, strs[i].s, strs[i].id, strs[i].len, i);
    if (fb) procStr(text, outText, used, idf, strs, l, size);
    if (lb) procStr(text, outText, used, idl, strs, l, size);
}

void proc(const char const *text, str *strs, int size, FILE *out) {
    int l = (int) strlen(text);
    char *outText;
    outText = (char *) malloc(sizeof(char) * 400002);
    strcpy(outText, text);
    int *used;
    used = (int *) malloc(sizeof(int) * (size_t) l);
    memset(used, -1, (size_t) l);
    for (int i = 0; i < l; ++i) used[i] = -1;
    int i;
    for (i = 0; i < size; ++i) {
        if (strs[i].len < 14) break;
        tableInit(strs[i].table, strs[i].s, strs[i].len);
        procStr(text, outText, used, i, strs, l, size);
    }

    for (int j = 0; j < i; ++j) {
        if (strs[i].free) lastProc(text, outText, used, i, strs, l, size);
    }

    for (int j = 0; j < l; ++j) {
        if (outText[j] == 'x') fprintf(out, "a");
        else fprintf(out, "%c", outText[j]);
    }
    fprintf(out, "\n");
}
