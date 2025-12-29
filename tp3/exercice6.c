#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    char cmd[100];

    if (argc != 2) {
        printf("Usage : %s fichier\n", argv[0]);
        return 1;
    }

    sprintf(cmd, "cat %s", argv[1]);
    system(cmd);

    return 0;
}
