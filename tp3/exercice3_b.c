#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

int is_in_tab(int *tab, int length, int val)
{
    pid_t p;
    int milieu = length / 2;
    int status;

    p = fork();

    if (p == 0)
    {
        for (int i = milieu + 1; i < length; i++)
        {
            if (tab[i] == val)
            {
                printf("Fils: j'ai trouve %d a l'indice %d\n", val, i);
                exit(i);
            }
        }
        exit(-1);
    }
    else
    {
        for (int i = 0; i <= milieu; i++)
        {
            if (tab[i] == val)
            {
                printf("Pere: j'ai trouve %d a l'indice %d\n", val, i);
                return i;
            }
        }

        waitpid(p, &status, 0);

        if (WIFEXITED(status))
        {
            int fils_result = WEXITSTATUS(status);
            if (fils_result != 255)
            {
                return fils_result;
            }
        }
    }

    return -1;
}

int main()
{
    int tab[] = {3, 5, 7, 9, 11, 13, 15, 17, 19, 13};
    int val = 5;
    int length = sizeof(tab) / sizeof(tab[0]);

    int result = is_in_tab(tab, length, val);

    if (result != -1)
        printf("La valeur %d est presente dans le tableau a l'indice %d.\n", val, result);
    else
        printf("La valeur %d n'est pas presente dans le tableau.\n", val);

    return 0;
}
