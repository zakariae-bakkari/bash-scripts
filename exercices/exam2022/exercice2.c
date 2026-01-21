#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#define N 5
int main(int argc, char *argv[])
{
    pid_t pids[N];

    for (int i = 0; i < N; i++) {
        if ((pids[i] = fork()) == 0) {
            printf("Fils %d, PID=%d\n", i, getpid());
            exit(i);
        }
    }

    for (int i = 0; i < N; i++) {
        int status;
        waitpid(pids[i], &status, 0);
        printf("Fils %d terminé avec code %d\n",
               i, WEXITSTATUS(status));
    }

    return 0;
}
