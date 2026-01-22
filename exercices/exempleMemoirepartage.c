/* writer.c */
#include <stdio.h>  /* Pour printf, perror */
#include <stdlib.h> /* Pour exit */
#include <unistd.h> /* Pour sleep */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
   int shm_id;
   key_t key = 5; /* Clé identifiant le segment [cite: 874] */
   int *data;

   /* * 1. Création du segment
    * IPC_CREAT : Crée le segment s'il n'existe pas
    * IPC_EXCL : Échoue si le segment existe déjà
    * 0600 : Droits de lecture/écriture pour l'utilisateur
    */
   shm_id = shmget(key, sizeof(int), IPC_CREAT | IPC_EXCL | 0600); //[cite: 878]

   if (shm_id == -1)
   {
      perror("Erreur lors de shmget");
      exit(1);
   }

   printf("Segment créé avec l'ID : %d\n", shm_id);

   /* 2. Attachement du segment à l'espace d'adressage */
   /* shmat retourne un pointeur void*, on le caste en int* */
   data = (int *)shmat(shm_id, NULL, 0); //[cite: 880]

   if (data == (int *)-1)
   {
      perror("Erreur lors de shmat");
      exit(2);
   }

   /* 3. Écriture de la valeur */
   *data = 1190; //[cite: 883]
   printf("J'ai écrit la valeur : %d\n", *data);

   /* 4. Pause pour laisser le temps au lecteur de lire */
   printf("Pause de 2 secondes...\n");
   sleep(2); //[cite: 884]

   /* 5. Détachement (optionnel avant destruction, mais propre) */
   shmdt(data);

   /* 6. Destruction du segment */
   /* IPC_RMID marque le segment pour suppression */
   if (shmctl(shm_id, IPC_RMID, NULL) == -1)
   { //[cite: 885]
      perror("Erreur lors de shmctl (suppression)");
      exit(3);
   }

   printf("Segment supprimé.\n");
   return 0;
}

/* reader.c */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main()
{
   int shm_id;
   key_t key = 5; /* Doit être la même clé que le writer */
   int *data;

   /* 1. Récupération de l'ID du segment existant (pas de IPC_CREAT) */
   shm_id = shmget(key, sizeof(int), 0); //[cite: 908]

   if (shm_id == -1)
   {
      perror("Erreur shmget (le segment n'existe pas ou droits refusés)");
      exit(1);
   }

   printf("ID récupéré : %d\n", shm_id);

   /* 2. Attachement */
   data = (int *)shmat(shm_id, NULL, 0); //[cite: 911]

   if (data == (int *)-1)
   {
      perror("Erreur shmat");
      exit(2);
   }

   /* 3. Lecture */
   printf("Valeur lue dans la mémoire partagée : %d\n", *data); //[cite: 917]

   /* 4. Détachement */
   /* On ne détruit pas le segment ici, c'est le rôle du writer */
   if (shmdt(data) == -1)
   {
      perror("Erreur shmdt");
      exit(3);
   }

   return 0;
}