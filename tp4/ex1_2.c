#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

// Fonction de traitement du signal SIGCHLD
void fin_fils(int sig)
{
    // -1 signifie "n'importe quel fils"
    printf("\n[Info] Un processus fils s'est terminé proprement (Zombie éliminé).\n");
}

int main()
{
    // 1. Association du signal SIGCHLD à la fonction fin_fils
    signal(SIGCHLD, fin_fils);

    if (!fork())
    {
        /* Code du FILS */
        printf("Fils : Je travaille...\n");
        for (int i = 0; i < 3; i++)
            sleep(1); // Simule un petit calcul
        printf("Fils : J'ai fini !\n");
        exit(0); // Le fils meurt ici -> Envoie SIGCHLD au père
    }
    /* Code du PÈRE */
    // Le père fait un calcul infini, il n'a pas de wait() bloquant ici.
    // Grâce au signal, il sera interrompu brièvement pour nettoyer le fils.
    while (1)
    {
        printf("Père : Je travaille en boucle infinie...\n");
        sleep(2);
    }
}