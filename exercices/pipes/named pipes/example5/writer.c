// programme writer.c envoie un message sur le tube mypipe
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
int main()
{
   int fd;
   char message[100];
   sprintf(message, "bonjour du writer [%d]", getpid());
   // Ouverture du tube mypipe en mode écriture
   fd = open("mypipe", O_WRONLY);
   printf("ici writer[%d] \n", getpid());
   if (fd != -1)
   { // Dépot d’un message sur le tube
      write(fd, message, strlen(message) + 1);
   }
   else
      printf(" désolé, le tube n'est pas disponible \n");
   close(fd);
   return 0;
}