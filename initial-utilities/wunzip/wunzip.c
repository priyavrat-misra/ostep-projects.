#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        fprintf(stdout, "wunzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    } else {
        int cnt;
        char c;
        while (--argc) {
            FILE* fp = fopen(*++argv, "r");
            if (fp == NULL) {
                fprintf(stdout, "wunzip: cannot open file\n");
                exit(EXIT_FAILURE);
            }
            while (1) {
                if (!fread(&cnt, sizeof(int), 1, fp)) { break; }
                fread(&c, sizeof(c), 1, fp);
                while (cnt--) { putchar(c); }
            }
        }
    }
    return EXIT_SUCCESS;
}
