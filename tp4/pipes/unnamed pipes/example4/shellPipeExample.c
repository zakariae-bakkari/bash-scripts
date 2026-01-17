#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#define R 0
#define W 1
int main(int argc, char *argv[])
{
   // simuler who | wc -l
   int d[2];
   pipe(d); // le processus pere va executer l'appel system pipe
   if (fork() == 0)
   {
      // fermeture du descripteur de l'ecture pour le fils
      close(d[R]);
      // redirection de la sortie standard vers le pipe
      dup2(d[W], 1);
      // fermeture du descripteur d'ecriture du pipe
      close(d[W]);
      // execution de la commande who
      execlp("who", "who", NULL);
   }
   else // le pere
   {
      // fermeture de l'ecriture
      close(d[W]);
      // redirection de l'entree standard vers le pipe
      dup2(d[R], 0);
      // fermeture du descripteur de lecture du pipe
      close(d[R]);
      // execution de la commande wc -l
      execlp("wc", "wc", "-l", NULL);
   }
   return 0;
}