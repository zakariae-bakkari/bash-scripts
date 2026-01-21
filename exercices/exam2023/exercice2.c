#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

/* ---------------- MODIF 3 ----------------
   Handler pour SIGUSR1 capté par TOUS les processus
*/
void handler_SIGUSR1(int sig) {
    printf("Signal SIGUSR1 reçu par le processus %d\n", getpid());
}

int main() {
    int n = 2, p = 0;
    int i;

    /* ---------------- MODIF 3 ----------------
       Installation du handler SIGUSR1 AVANT les fork
       → tous les processus héritent du handler
    */
    signal(SIGUSR1, handler_SIGUSR1);

    for (i = 0; i < n; i++) {
        if (fork() == 0) {
            n--;
            p = 0;
        } else {
            p++;
        }
    }

    printf("Processus %d : n=%d, p=%d\n", getpid(), n, p);

    /* ---------------- MODIF 2 ----------------
       Le père attend ses fils et détecte les fins anormales
    */
    if (p) {
        int status;
        pid_t pid_fils;

        while ((pid_fils = wait(&status)) > 0) {
            if (!WIFEXITED(status)) {
                printf("Fin anormale du fils %d du processus %d\n",
                       pid_fils, getpid());
            }
        }
    }
    else {
        /* ---------------- Code initial ----------------
           Le fils envoie SIGUSR1 au père
        */
        kill(getppid(), SIGUSR1);
        sleep(2);
    }

    exit(0);
}
