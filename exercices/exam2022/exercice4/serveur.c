#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <string.h>

int main() {
    mkfifo("cli2serv", 0666);
    mkfifo("serv2cli", 0666);

    int fd_in = open("cli2serv", O_RDONLY);
    int fd_out = open("serv2cli", O_WRONLY);

    char req[100];
    while (read(fd_in, req, sizeof(req)) > 0) {
        if (strcmp(req, "bye") == 0) {
            write(fd_out, "ciao", 4);
            break;
        }

        int op1, op2;
        char op;
        sscanf(req, "%d%1s%d", &op1, &op, &op2);

        int res = (op == '+') ? op1 + op2 : 0;
        char rep[50];
        sprintf(rep, "%d", res);
        write(fd_out, rep, strlen(rep) + 1);
    }
    return 0;
}
