#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int compteur = 0;

/* Fonction exécutée par le thread d'incrémentation */
void* incrementer(void* arg)
{
    for (int i = 0; i < 5; i++) {
        compteur++;
        printf("Thread incrementer : compteur = %d\n", compteur);
        sleep(1);
    }
    pthread_exit(NULL);
}

/* Fonction exécutée par le thread de décrémentation */
void* decrementer(void* arg)
{
    for (int i = 0; i < 5; i++) {
        compteur--;
        printf("Thread decrementer(%d) : compteur = %d\n", i,compteur);
        sleep(1);
    }
    pthread_exit(NULL);
}

int main()
{
    pthread_t th1, th2;

    printf("Valeur initiale du compteur = %d\n", compteur);

    pthread_create(&th1, NULL, incrementer, NULL);
    pthread_create(&th2, NULL, decrementer, NULL);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    printf("Valeur finale du compteur = %d\n", compteur);

    return 0;
}
