#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/resource.h>
#include "read.h"
#include "strings.h"

typedef struct {
    char *s;
    int len;
} str;

char *text;
char **strings;
str *strs;
int sSize;

int calc(const void *a, const void *b) {
    return ((str *) b)->len - ((str *) a)->len;
}

int mainPrg(int, char **);

int main(int argc, char **argv) {

    struct rusage u;
    struct timeval start, end;

    getrusage(RUSAGE_SELF, &u);
    start = u.ru_utime;

    mainPrg(argc, argv);

    getrusage(RUSAGE_SELF, &u);
    end = u.ru_utime;

    fprintf(stderr, "%lf\n", (double) (end.tv_sec - start.tv_sec) + (double) (end.tv_usec - start.tv_usec) * 1e-6);

    return (0);
}

int mainPrg(int argc, char **argv) {
    assert(argc == 3);
    FILE *inputFile = fopen(argv[1], "r");
    assert(inputFile != NULL);
    FILE *outputFile = fopen(argv[2], "w");
    assert(outputFile != NULL);

    text = (char *) malloc(sizeof(char) * 400002);
    strings = (char **) malloc(sizeof(char *) * 400002);
    for (int i = 0; i < 400002; ++i) strings[i] = (char *) malloc(sizeof(char) * 400002);
    readFile(inputFile, text, strings, &sSize);
    strs = (str *) malloc(sizeof(str) * (size_t) sSize);
    for (int i = 0; i < sSize; ++i) {
        strs[i].len = (int) strlen(strings[i]);
        strs[i].s = (char *) malloc(sizeof(char) * (size_t) (strs[i].len + 1));
        strcpy(strs[i].s, strings[i]);
    }
    free(strings);

    qsort(strs, (size_t) sSize, sizeof(str), calc);

    int l = (int) strlen(text);
    for (int i = 0; i < l; ++i) {
        if (text[i] == 'x') fprintf(outputFile, "a");
        else fprintf(outputFile, "%c", text[i]);
    }
    fprintf(outputFile, "\n");

    fclose(inputFile);
    fclose(outputFile);
    return 0;
}
