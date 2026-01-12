#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
   pid_t pid = fork(); // fils numero 1
   if (pid == 0)
   {
      printf("execution de who par execlp :\n");
      if (execlp("who", "who", NULL) == -1)
      {
         printf("Erreur lors de l'exécution de 'who'");
         exit(-1);
      }
   }
   else // le pere
   {
      wait(NULL);          // attendre la fin du fils 1
      pid_t pid2 = fork(); // fils numero 2
      if (pid2 < 0)
      {
         printf("Erreur lors de la creation du processus pour ps\n");
         exit(-1);
      }

      // fils 2
      if (pid2 == 0)
      {
         printf("\nexecution de ps par execlp :\n");
         if (execlp("ps", "ps", NULL) == -1)
         {
            perror("Erreur lors de l'exécution de 'ps'");
            exit(-1);
         }
      }
      else // le pere
      {
         wait(NULL);          // attendre la fin du fils 2
         pid_t pid3 = fork(); // fils numero 3
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
               perror("Erreur lors de l'exécution de 'ls -l'");
               exit(-1);
            }
         }
         else // le pere
         {
            wait(NULL); // attendre la fin du fils 3
         }
      }
   }

   return 0;
}