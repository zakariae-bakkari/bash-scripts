#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{

   // Premier fils pour who
   pid_t pid1 = fork();
   if (pid1 < 0)
   {
      printf("Erreur lors de la creation du processus pour who");
      exit(-1);
   }
   if (pid1 == 0)
   {
      if (execlp("who", "who", NULL) == -1)
      {
         printf("Erreur lors de l'execution de who \n");
         exit(-1);
      }
   }

   // Deuxieme fils pour ps
   pid_t pid2 = fork();
   if (pid2 < 0)
   {
      printf("Erreur lors de la creation du processus pour ps\n");
      exit(-1);
   }
   if (pid2 == 0)
   {
      printf("\nexecution de ps par execlp :\n");
      if (execlp("ps", "ps", NULL) == -1)
      {
         printf("Erreur lors de l'execution de ps\n");
         exit(-1);
      }
   }

   // Troisieme fils pour ls -l
   pid_t pid3 = fork();
   if (pid3 < 0)
   {
      printf("Erreur lors de la creation du processus pour ls -l\n");
      exit(-1);
   }
   if (pid3 == 0)
   {
      printf("\nexecution de ls -l par execlp :\n");
      if (execlp("ls", "ls", "-l", NULL) == -1)
      {
         printf("Erreur lors de l'execution de ls -l\n");
         exit(-1);
      }
   }

   // Le pere attend tous les fils
   for (int i = 0; i < 3; i++)
   {
      wait(NULL);
   }

   printf("\nToutes les commandes ont ete executees dans background comme & \n");
   return 0;
}