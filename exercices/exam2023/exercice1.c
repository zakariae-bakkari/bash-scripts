#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int main() {
    pid_t pid = fork();

    if (pid == 0) {
        // Fils : calcul infini
        while (1) {
            // simulation de calcul
        }
    } else {
        char c;
        while (1) {
            printf("Menu: s (stop), r (resume), q (quit): ");
            scanf(" %c", &c);

            if (c == 's') {
                kill(pid, SIGSTOP);
            } else if (c == 'r') {
                kill(pid, SIGCONT);
            } else if (c == 'q') {
                kill(pid, SIGKILL);
                break;
            }
        }
    }
    return 0;
}
