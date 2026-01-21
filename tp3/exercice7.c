#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <commande> <option/fichier>\n", argv[0]);
        return 1;
    }

    if (execvp(argv[1], &argv[1]) == -1)
    {
        perror("Erreur lors de l'execution de la commande");
        exit(EXIT_FAILURE);
    }

    return 0;
}
