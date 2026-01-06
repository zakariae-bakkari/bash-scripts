#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s <commande>\n", argv[0]);
        return 1;
    }

    if (argc > 2)
    {
        execlp(argv[1], argv[1], argv[2], NULL);
    }
    pid_t pid = fork(); // créer un processus fils

    if (pid < 0)
    {
        printf("Erreur lors du fork\n");
        return 1;
    }

    if (pid == 0)
    {
        // processus fils
        execlp(argv[1], argv[1], NULL);
        printf("Erreur lors de l'execution de la commande\n");
        exit(1);
    }
    else
    {
        // processus parent
        int status;
        wait(&status);
        if (WIFEXITED(status))
        {
            printf("La commande s'est terminée avec le code %d\n", WEXITSTATUS(status));
        }
    }

    return 0;
}
