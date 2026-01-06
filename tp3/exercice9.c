#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

char **separer_commande(char commande[])
{
   int taille = strlen(commande);
   char **table_commande = malloc(100 * sizeof(char *));
   int indice = 0;
   char mot[256];
   int mot_index = 0;

   for (int i = 0; i <= taille; i++)
   {
      if (commande[i] != ' ' && commande[i] != '\0')
      {
         mot[mot_index++] = commande[i];
      }
      else
      {
         if (mot_index > 0)
         {
            mot[mot_index] = '\0';
            table_commande[indice] = malloc((mot_index + 1) * sizeof(char));
            strcpy(table_commande[indice], mot);
            indice++;
            mot_index = 0;
         }
      }
   }
   table_commande[indice] = NULL; // Null-terminate the array
   return table_commande;
}

int main()
{
   char commande[256];
   pid_t pid;
   do
   {
      printf("monshell> ");
      scanf(" %255[^\n]", commande);
      if (strcmp(commande, "exit") == 0)
      {
         exit(-1);
      }
      char **table_commande = separer_commande(commande);

      pid = fork();
      if (pid == 0)
      {
         execvp(table_commande[0], table_commande);
         perror("execlp");
         exit(-1);
      }
      wait(NULL);

      
      for (int i = 0; table_commande[i] != NULL; i++)
      {
         free(table_commande[i]);
      }
      free(table_commande);
   } while (1);

   return 0;
}