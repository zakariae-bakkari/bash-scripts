// programme reader.c lit un message à partir du tube mypipe
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
int main()
{
   int fd, n;
   char message[100];
   // ouverture du tube mypipe en mode lecture
   fd = open("mypipe", O_RDONLY);
   printf("ici reader[%d] \n", getpid());
   if (fd != -1)
   { // récupérer un message du tube, taille maximale est 100.
      while ((n = read(fd, message, 100)) > 0)
         // n est le nombre de caractères lus
         printf("%s\n", message);
   }
   else
      printf("désolé, le tube n'est pas disponible\n");
   close(fd);
   return 0;
}