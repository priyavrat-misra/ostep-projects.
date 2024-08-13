#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE (128)

int main(int argc, char* argv[]) {
    char buffer[BUFFER_SIZE];
    while (--argc) {
        FILE *fp = fopen(*++argv, "r");
        if (!fp) {
            printf("wcat: cannot open file\n");
            exit(EXIT_FAILURE);
        }

        while (fgets(buffer, BUFFER_SIZE, fp)) {
            printf("%s", buffer);
        }
    }
    return EXIT_SUCCESS;
}
