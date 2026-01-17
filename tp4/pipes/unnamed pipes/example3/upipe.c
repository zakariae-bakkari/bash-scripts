#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#define R 0
#define W 1
int main()
{
   int d[2];
   pipe(d); // le processus pere va executer l'appel system pipe
   int valeurRecupere;
   if (fork() == 0)
   {
      // fermeture du descripteur de l'ecture pour le fils
      close(d[R]);
      valeurRecupere = 10;
      printf("Fils: Envoi de la valeur %d dans le pipe.\n", valeurRecupere);
      write(d[W], &valeurRecupere, sizeof(int));// this is the write operation will write the value to the pipe with descriptor d[W]
      close(d[W]); // fermeture du descripteur de l'ecriture du fils
   }
   else // le pere
   {
      close(d[W]); // fermeture de l'ecriture
      read(d[R], &valeurRecupere, sizeof(int));// lecture de la valeur depuis le pipe avec le descripteur d[R]
      printf("Pere: Valeur reçue depuis le pipe: %d\n", valeurRecupere);
      close(d[R]);
   }

   return 0;
}