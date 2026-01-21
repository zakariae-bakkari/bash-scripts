#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

struct msg_req
{
    long mtype;
    pid_t pid_client;
    int nb1;
    int nb2;
};
struct msg_rep
{
    long mtype;
    int somme;
};

int main()
{
    key_t key = ftok("serveur", 65);
    if (key == -1)
    {
        perror("errors de ftok");
        exit(-1);
    }

    int msgid = msgget(key, 0666); // Connexion à la file existante

    struct msg_req requete;
    struct msg_rep reponse;

    requete.mtype = 1; // Type réservé aux requêtes (priorite)
    requete.pid_client = getpid();
    requete.nb1 = 10;
    requete.nb2 = 20;

    // Envoi requête
    msgsnd(msgid, &requete, sizeof(requete) - sizeof(long), 0);

    // Attente réponse (Type = MON PID)
    msgrcv(msgid, &reponse, sizeof(reponse) - sizeof(long), requete.pid_client, 0);

    printf("Client %d : La somme est %d\n", getpid(), reponse.somme);
    return 0;
}