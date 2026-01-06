#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
   printf("argc=%d\n", argc);
   for (int i = 0; i < argc; i++)
   {
      printf("argv[%d]=%s\n", i, argv[i]);
   }

   if (argc < 2)
   {
      printf("on doit avoir au mois un parametre comme suite ./ex7 <cammande>\nvous pouvez utiliser ./ex7");
      exit(-1);
   }

   pid_t p;
   p = fork(); // creation d'un fils

   if (p < 0)
   {
      printf("Erreur lors du fork\n");
      return 1;
   }

   if (p == 0) // pour le fils
   {
      execlp(argv[1], argv[1], NULL); // argv[1] est deuxiem element dans le tableau => le premier parametre
      printf("errors dans execlp\n");
      exit(-1); // au cas d'erreur du execlp
   }
   else
   {
      int status;
      wait(&status);
      if (WIFEXITED(status))
      {
         printf("le programe execute normalement avec le code de retour : %d", WEXITSTATUS(status));
      }
   }

   return 0;
}