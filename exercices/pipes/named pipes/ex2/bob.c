#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_A_TO_B "/tmp/fifo_a_to_b"
#define FIFO_B_TO_A "/tmp/fifo_b_to_a"

int main() {
    int fd_write, fd_read;
    char message_envoye[100];
    char message_recu[100];

    printf("--- BOB ---\n");

    // 1. Ouverture en LECTURE depuis Alice
    // Cela débloque le premier open() d'Alice !
    printf("Connexion au tube de réception (attente d'Alice)...\n");
    fd_read = open(FIFO_A_TO_B, O_RDONLY);
    printf("Tube de réception connecté !\n");

    // 2. Ouverture en ÉCRITURE vers Alice
    // Cela débloque le deuxième open() d'Alice !
    printf("Connexion au tube d'envoi...\n");
    fd_write = open(FIFO_B_TO_A, O_WRONLY);
    printf("Tube d'envoi connecté ! Chat prêt.\n");

    while(1) {
        // --- ATTENTE D'ALICE (Bob ne parle qu'en deuxième) ---
        printf("... En attente d'Alice ...\n");
        read(fd_read, message_recu, 100);

        if (strcmp(message_recu, "exit") == 0) {
            printf("Alice a quitté la conversation.\n");
            break;
        }
        printf("Alice a dit : %s\n", message_recu);

        // --- TOUR DE BOB ---
        printf("Bob (vous) : ");
        fgets(message_envoye, 100, stdin);
        
        message_envoye[strcspn(message_envoye, "\n")] = 0;

        write(fd_write, message_envoye, strlen(message_envoye) + 1);

        if (strcmp(message_envoye, "exit") == 0) break;
    }

    close(fd_write);
    close(fd_read);
    return 0;
}