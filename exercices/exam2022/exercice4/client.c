#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
    int fd_out = open("cli2serv", O_WRONLY);
    int fd_in = open("serv2cli", O_RDONLY);

    char req[100];
    while (1) {
        fgets(req, 100, stdin);
        req[strcspn(req, "\n")] = 0;

        write(fd_out, req, strlen(req) + 1);

        if (strcmp(req, "bye") == 0)
            break;

        char rep[50];
        read(fd_in, rep, sizeof(rep));
        printf("Résultat: %s\n", rep);
    }
    return 0;
}
