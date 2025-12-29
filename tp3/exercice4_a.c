#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0) { // processus fils
        execl("/bin/ps", "ps", "-l", NULL);
        perror("Erreur execl");
        exit(1);
    }
    else { // processus père
        wait(&status);
        printf("Code retour de ps : %d\n", WEXITSTATUS(status));
    }

    return 0;
}
