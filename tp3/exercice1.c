#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t p;

    p = fork();//f1

    if (p == 0) { // fils 1
        for (int i = 1; i <= 50; i++) {
            printf("%d ", i);
        }
        return 0;
    }

    // attendre la fin du premier fils
    wait(NULL);

    
    p = fork();//f2

    if (p == 0) { // fils 2
        for (int i = 51; i <= 100; i++) {
            printf("%d ", i);
        }
        return 0;
    }

    // attendre la fin du deuxieme fils
    wait(NULL);

    return 0;
}
