#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main()
{
   char commande[256];
   pid_t pid;
   do
   {
      printf("monshell> ");
      scanf("%255s", commande);
      if (strcmp(commande, "exit") == 0)
      {
         exit(-1);
      }

      pid = fork();
      if (pid == 0)
      {
         if (execlp(commande, commande, NULL) == -1)
         {
            printf("salam");
         }
      }
      wait(NULL);
   } while (1);

   return 0;
}