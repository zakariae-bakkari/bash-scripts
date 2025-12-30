#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t p1, p2, fin;
    int status;

    p1 = fork();
    if (p1 == 0) {
        execl("/bin/ls", "ls", "-l", NULL);
        exit(1);
    }

    p2 = fork();
    if (p2 == 0) {
        execl("/bin/ps", "ps", "-l", NULL);
        exit(1);
    }

    fin = wait(&status);
    printf("Premier processus terminé : PID = %d\n ,code de retour: %d", fin, WEXITSTATUS(status));

    wait(NULL); // attendre le fils 2
    return 0;
}
