#include <stdio.h>
#include <pthread.h>

int tab[] = {5,12,8,20,3,15,1,30};
int size = 8;

void* thr1(void* arg) {
    for (int i = 0; i < size/2; i++)
        if (tab[i] >= 10) printf("%d ", tab[i]);
    return NULL;
}

void* thr2(void* arg) {
    for (int i = size/2; i < size; i++)
        if (tab[i] >= 10) printf("%d ", tab[i]);
    return NULL;
}

int main() {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, thr1, NULL);
    pthread_create(&t2, NULL, thr2, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    return 0;
}
