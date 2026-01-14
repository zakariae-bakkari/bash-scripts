#include <stdio.h>
#include <pthread.h>

int compteur = 0; // Variable globale partagée [cite: 324]
#define N 1000000

void* incrementer(void* arg) {
    for(int i=0; i<N; i++) {
        compteur++; 
    }
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, incrementer, NULL);
    pthread_create(&t2, NULL, incrementer, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    
    printf("Valeur attendue : %d\n", 2*N);
    printf("Valeur finale   : %d\n", compteur);
    return 0;
}