#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Partie 4.1 : Alphabet
void *thread_min(void *arg)
{
    for (char c = 'a'; c <= 'z'; c++)
        printf("%c", c);
    printf("\n");
    return NULL;
}
void *thread_maj(void *arg)
{
    for (char c = 'A'; c <= 'Z'; c++)
        printf("%c", c);
    printf("\n");
    return NULL;
}


int main()
{
    pthread_t t1, t2;

    // --- Exec 4.1 ---
    pthread_create(&t1, NULL, thread_min, NULL);
    pthread_create(&t2, NULL, thread_maj, NULL);
    pthread_join(t1, NULL); // Attendre la fin [cite: 222]
    pthread_join(t2, NULL);
    printf("\n--- Fin 4.1 ---\n");

    return 0;
}