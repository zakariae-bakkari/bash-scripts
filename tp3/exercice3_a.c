#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

int main() {
    pid_t p;

    p = fork();

    if (p == 0) { // fils
        srand(time(NULL) ^ getpid()); // pour eviter la meme graine
        int n = rand() % 101;
        exit(n);
    } 
    else {
        int status;
        waitpid(p, &status, 0);

        if (WIFEXITED(status)) {
            int ret = WEXITSTATUS(status);
            printf("Le fils a termine avec le code: %d\n", ret);
        }
    }

    return 0;
}
