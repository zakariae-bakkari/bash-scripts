#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// Partie 4.1 : Alphabet
void* thread_min(void* arg) {
    for(char c='a'; c<='z'; c++) printf("%c", c);
    return NULL;
}
void* thread_maj(void* arg) {
    for(char c='A'; c<='Z'; c++) printf("%c", c);
    return NULL;
}

// Partie 4.2 : Écriture fichier
FILE *fichier; // Ressource partagée 

void* ecrire_1(void* arg) {
    for(int i=0; i<=100000; i++) fprintf(fichier, "%d\n", i);
    return NULL;
}
void* ecrire_2(void* arg) {
    for(int i=1000000; i<=1100000; i++) fprintf(fichier, "%d\n", i);
    return NULL;
}

int main() {
    pthread_t t1, t2;

    // --- Exec 4.1 ---
    pthread_create(&t1, NULL, thread_min, NULL);
    pthread_create(&t2, NULL, thread_maj, NULL);
    pthread_join(t1, NULL); // Attendre la fin [cite: 222]
    pthread_join(t2, NULL);
    printf("\n--- Fin 4.1 ---\n");

    // --- Exec 4.2 ---
    fichier = fopen("output.txt", "w");
    pthread_create(&t1, NULL, ecrire_1, NULL);
    pthread_create(&t2, NULL, ecrire_2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    fclose(fichier);
    printf("Fichier écrit. Ouvrez output.txt pour voir le mélange !\n");
    
    return 0;
}