#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s cmd1 cmd2 [args...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    signal(SIGHUP, SIG_IGN);

    // Première commande (sans arguments)
    if (fork() == 0) {
        execlp(argv[1], argv[1], NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    }
    wait(NULL);

    // Deuxième commande (avec arguments)
    if (fork() == 0) {
        execvp(argv[2], &argv[2]);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    wait(NULL);

    return 0;
}
