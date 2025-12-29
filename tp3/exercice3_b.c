#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int is_in_tab(int *tab, int length, int val)
{
    pid_t p;
    int milieu = length / 2;
    int trouve_parent = 0;
    int trouve_fils = 0;
    int status;

    p = fork();

    if (p == 0) {
        for (int i = milieu + 1; i < length; i++) {
            if (tab[i] == val) {
                printf("Fils: j'ai trouve %d a la position %d\n", val, i + 1);
                exit(1);
            }
        }
        exit(0); 
    }
    else {
        for (int i = 0; i <= milieu; i++) {
            if (tab[i] == val) {
                printf("Pere: j'ai trouve %d a la position %d\n", val, i + 1);
                trouve_parent = 1;
                break;
            }
        }

        waitpid(p, &status, 0);

        if (WIFEXITED(status)) {
            trouve_fils = WEXITSTATUS(status);
        }
    }

    return (trouve_parent || trouve_fils);
}

int main()
{
    int tab[] = {3, 5, 7, 9, 11, 13, 15, 17, 19, 13};
    int val = 13;
    int length = sizeof(tab) / sizeof(tab[0]);

    int result = is_in_tab(tab, length, val);

    if (result)
        printf("La valeur %d est presente dans le tableau.\n", val);
    else
        printf("La valeur %d n'est pas presente dans le tableau.\n", val);

    return 0;
}
