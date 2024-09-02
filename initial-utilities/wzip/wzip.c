#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
    if (argc == 1) {
        fprintf(stdout, "wzip: file1 [file2 ...]\n");
        exit(EXIT_FAILURE);
    } else {
        int c = EOF, nc, cnt = 1;
        while (--argc) {
            FILE* fp = fopen(*++argv, "r");
            if (fp == NULL) {
                fprintf(stdout, "wzip: cannot open file\n");
                exit(EXIT_FAILURE);
            }

            // read first char of first file
            if (c == EOF) { c = getc(fp); }

            while (1) {
                while ((nc = getc(fp)) == c) { ++cnt; }
                if (nc == EOF) { break; }
                fwrite(&cnt, sizeof(int), 1, stdout);
                putc(c, stdout);
                c = nc, cnt = 1;
            }

            fclose(fp);
        }

        // write last char of last file
        fwrite(&cnt, sizeof(int), 1, stdout);
        putc(c, stdout);
    }

    return EXIT_SUCCESS;
}
