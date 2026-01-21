#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Partie 4.2 : Écriture fichier
FILE *fichier; // Ressource partagée

void *ecrire_1(void *arg)
{
    for (int i = 0; i <= 100000; i++)
        fprintf(fichier, "%d\n", i);
    printf("\n");
    return NULL;
}
void *ecrire_2(void *arg)
{
    for (int i = 1000000; i <= 1100000; i++)
        fprintf(fichier, "%d\n", i);
    printf("\n");
    return NULL;
}

int main()
{
    pthread_t t1, t2;

    fichier = fopen("output.txt", "w");
    pthread_create(&t1, NULL, ecrire_1, NULL);
    pthread_create(&t2, NULL, ecrire_2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    fclose(fichier);
    printf("Fichier écrit. Ouvrez output.txt pour voir le mélange !\n");

    return 0;
}