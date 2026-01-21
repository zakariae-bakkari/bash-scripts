#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

pid_t fils_aine;

void handler_cadet(int sig) {
    kill(fils_aine, SIGUSR2);
}

void handler_aine(int sig) {
    exit(0);
}

int main() {
    pid_t fils_cadet;

    fils_aine = fork();
    if (fils_aine == 0) {
        signal(SIGUSR2, handler_aine);
        pause();
    }

    fils_cadet = fork();
    if (fils_cadet == 0) {
        signal(SIGUSR1, handler_cadet);
        pause();
    }

    sleep(1);
    kill(fils_cadet, SIGUSR1);

    wait(NULL);
    wait(NULL);
    return 0;
}
