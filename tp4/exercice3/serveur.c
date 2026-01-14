#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

// Définition des structures (comme ci-dessus)
struct msg_req { long mtype; pid_t pid_client; int nb1; int nb2; };
struct msg_rep { long mtype; int somme; };

int main() {
    key_t key = ftok("serveur", 65); // Génération clé [cite: 1063]
    int msgid = msgget(key, 0666 | IPC_CREAT); // Création file [cite: 1084]

    struct msg_req requete;
    struct msg_rep reponse;

    printf("Serveur prêt...\n");
    while(1) {
        // Réception d'un message de type 1
        msgrcv(msgid, &requete, sizeof(requete)-sizeof(long), 1, 0);
        
        printf("Reçu de %d : %d + %d\n", requete.pid_client, requete.nb1, requete.nb2);

        // Calcul
        reponse.mtype = requete.pid_client; // Cible le client spécifique
        reponse.somme = requete.nb1 + requete.nb2;

        // Envoi
        msgsnd(msgid, &reponse, sizeof(reponse)-sizeof(long), 0);
    }
    return 0;
}