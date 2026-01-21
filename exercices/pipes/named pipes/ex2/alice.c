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

    printf("--- ALICE ---\n");

    // 1. Ouverture en ÉCRITURE vers Bob
    // BLOQUANT tant que Bob n'ouvre pas ce tube en lecture [cite: 406-407]
    printf("Connexion au tube d'envoi (attente de Bob)...\n");
    fd_write = open(FIFO_A_TO_B, O_WRONLY);
    printf("Tube d'envoi connecté !\n");

    // 2. Ouverture en LECTURE depuis Bob
    // Bob doit ouvrir ce tube en écriture pour débloquer Alice ici
    printf("Connexion au tube de réception...\n");
    fd_read = open(FIFO_B_TO_A, O_RDONLY);
    printf("Tube de réception connecté ! Chat prêt.\n");


while(1) {
   // --- TOUR D'ALICE (Ecriture) ---
   printf("Alice (vous) : ");
   // Nettoyage du buffer mémoire avant d'écrire
   memset(message_envoye, 0, sizeof(message_envoye)); 
   
   if (fgets(message_envoye, 100, stdin) == NULL) break;
   
   // Enlever le saut de ligne \n proprement
   message_envoye[strcspn(message_envoye, "\n")] = 0;

   // Envoi du message
   write(fd_write, message_envoye, strlen(message_envoye));

   if (strcmp(message_envoye, "exit") == 0) break;

   // --- ATTENTE DE BOB (Lecture) ---
   printf("... En attente de Bob ...\n");
   
   // Nettoyage du buffer de réception
   memset(message_recu, 0, sizeof(message_recu));
   
   // On utilise 'n' pour savoir combien d'octets on a vraiment reçus
   int n = read(fd_read, message_recu, sizeof(message_recu)-1);
   
   if (n > 0) {
       message_recu[n] = '\0'; // On force la fin de chaîne ici !
       
       if (strcmp(message_recu, "exit") == 0) {
           printf("Bob a quitté la conversation.\n");
           break;
       }
       printf("Bob a dit : %s\n", message_recu);
   } else {
       // Si n <= 0, le tube est cassé ou vide
       perror("Erreur de lecture ou déconnexion");
       break;
   }
}

    close(fd_write);
    close(fd_read);
    return 0;
}