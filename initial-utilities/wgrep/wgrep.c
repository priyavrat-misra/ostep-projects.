#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MOD (101)
#define MUL (128)

int calculateHash(const char* term, int n) {
    int hash = 0;
    while (n--) { hash = (hash * MUL + *term++) % MOD; }
    return hash;
}

bool areAllCharEqual(const char* pattern, const char* window) {
    while (*pattern)
        if (*pattern++ != *window++)
            return false;

    return true;
}

void printMatches(FILE* fp, const char* pattern, const int n, const int patternHash, const int msp) {
    char* line = NULL;
    size_t _ = 0;
    ssize_t len;
    while ((len = getline(&line, &_, fp)) != EOF) {
        if (len - 1 < n) { continue; }
        int windowHash = calculateHash(line, n);
        if (windowHash == patternHash && areAllCharEqual(pattern, line)) {
            fprintf(stdout, "%s", line);
        } else {
            for (int i = 1; i < len - n; ++i) {
                windowHash = windowHash - line[i - 1] * msp % MOD;
                if (windowHash < 0) { windowHash += MOD; }
                windowHash = windowHash * MUL % MOD;
                windowHash = (windowHash + line[i - 1 + n]) % MOD;
                if (windowHash == patternHash && areAllCharEqual(pattern, line + i)) {
                    fprintf(stdout, "%s", line);
                    break;
                }
            }
        }
    }
    free(line);
}

int main(int argc, char* argv[]) {
    if (argc == 1) {
        fprintf(stdout, "wgrep: searchterm [file ...]\n");
        exit(EXIT_FAILURE);
    } else {
        const char* pattern = argv[1];
        const int n = strlen(pattern);
        const int patternHash = calculateHash(pattern, n);

        int msp = 1;  // most significant place
        for (int i = 1; i < n; ++i) { msp = (msp * MUL) % MOD; }

        if (argc == 2) {
            printMatches(stdin, pattern, n, patternHash, msp);
        } else {
            argc -= 2, argv += 2;
            while (argc--) {
                FILE* fp = fopen(*argv++, "r");
                if (fp == NULL) {
                    fprintf(stdout, "wgrep: cannot open file\n");
                    exit(EXIT_FAILURE);
                }
                printMatches(fp, pattern, n, patternHash, msp);
                fclose(fp);
            }
        }
    }
    return EXIT_SUCCESS;
}
