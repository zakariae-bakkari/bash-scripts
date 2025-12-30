#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int status;

    char *args[] = {"ps", "-l", NULL};

    pid = fork();

    if (pid == 0) {
        execv("/bin/ps", args);
        printf("Erreur lors de l'execution de ps\n");
        exit(1);
    }
    else {
        wait(&status);
        printf("Code retour de ps : %d\n", WEXITSTATUS(status));
    }

    return 0;
}
