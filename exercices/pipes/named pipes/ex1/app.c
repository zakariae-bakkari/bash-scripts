#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>

#define FIFO_PATH "/tmp/my_log_fifo"

int main()
{
   int fd;
   char message[100];
   char nom[30];

   printf("App [%d] : Tentative de connexion au logger...\n", getpid());

   // 1. Ouverture en écriture seule
   // Bloque si le logger n'est pas encore lancé (sauf si O_NONBLOCK est utilisé)
   fd = open(FIFO_PATH, O_WRONLY);
   if (fd == -1)
   {
      perror("Erreur : Le tube n'existe pas (lancez logger d'abord)");
      return 1;
   }

   printf("App : Connecté ! Tapez 'exit' pour quitter.\n");

   // 2. Boucle d'écriture
   printf("entrer votre nom : ");
   scanf("%30s", nom);
   while (1)
   {
      printf("(%s) > ", nom);
      // Utilisation de scanf sécurisé pour un mot, ou fgets pour une phrase
      char temp[100];
      scanf(" %[^\n]99s", temp);
      snprintf(message, sizeof(message), "%s: %s", nom, temp);
      // Envoi du message (taille réelle + 1 pour le caractère nul \0)
      write(fd, message, strlen(message) + 1);

      if (strcmp(temp, "exit") == 0)
      {
         break;
      }
   }

   close(fd);
   return 0;
}