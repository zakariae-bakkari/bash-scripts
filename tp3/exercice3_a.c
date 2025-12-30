#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

int main() {
    pid_t p;

    p = fork();

    if (p == 0) { // fils
        srand(time(NULL) ^ getpid()); // pour eviter la meme graine
        int n = rand() % 101;
        sleep(2000); // pour simuler un traitement long
        return n;
    } 
    else {
        int status;
        waitpid(p, &status, 0);// status recupere le status de termiison
        printf("status: %d\n", status);
        if (WIFEXITED(status))
        {
            int ret = WEXITSTATUS(status);
            printf("Le fils a termine avec le code: %d\n", ret);
        }
        else if (WIFSIGNALED(status)){
            printf("Le fils a ete tue par le signal: %d\n", WTERMSIG(status));
        }
        
    }

    return 0;
}
