#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid;
    int status;

    pid = fork();

    if (pid == 0) { // processus fils
        if(execl("/bin/ps", "ps", "-l", NULL) == -1) {
        printf("Erreur lors de l'execution de ps\n");
        exit(1);}
    }
    else { // processus père
        wait(&status);
        printf("Code retour de ps : %d\n", WEXITSTATUS(status));
    }

    return 0;
}
