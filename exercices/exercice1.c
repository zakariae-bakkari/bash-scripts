// Exercice 1
// Le signal SIGCHLD est un signal qui est automatiquement envoyé par le fils à son père lorsque
// le fils se termine (par un exit, un return, ou autre).
// Ajoutez une fonction et le code nécessaire pour que le père n’attende jamais son fils de façon
// bloquante et le fils ne devienne pas zombie.
/*0*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
void handler(int sig)
{ /*A*/
   int status;
   wait(&status); // Nettoie le fils terminé
} /*B*/
int main(int argc, char *argv[])
{ /*1*/
   signal(SIGCHLD, handler); // Association du signal SIGCHLD à la fonction handler
   if (!fork())
   { /*2*/
      for (int i = 0; i < 10; i++)
         ; // simule un petit calcul
      /*3*/
      exit(1);
      /*4*/
   } /*5*/
   while (1)
      ; // Simule un calcul infini
   /*6*/
}