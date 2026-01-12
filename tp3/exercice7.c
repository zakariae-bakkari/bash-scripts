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

    if (argc > 2)
    {
        execlp(argv[1], argv[1], argv[2], NULL);
        printf("Erreur lors de l'execution de la commande\n");
        exit(1);
    }
    else
    {
        execlp(argv[1], argv[1], NULL);
        printf("Erreur lors de l'execution de la commande\n");
        exit(1);
    }

    return 0;
}
