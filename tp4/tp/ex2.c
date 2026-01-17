#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

#define R 0
#define W 1

int main()
{
   int d[2];
   pipe(d); // Pipe between grep and wc

   if (fork() == 0) // Child 1 (grep root)
   {
      int d2[2];
      pipe(d2); // Pipe between ps and grep

      if (fork() == 0) // Child 2 (ps -aux)
      {
         close(d2[R]); // Close unused read end
         dup2(d2[W], 1); // Redirect stdout to write end of pipe
         close(d2[W]); // Close write end after redirection

         execlp("ps", "ps", "-aux", NULL); // Execute ps -aux
         perror("execlp ps"); // Error handling if execlp fails
         _exit(1);
      }

      // Parent process of Child 2 (grep root)
      close(d2[W]); // Close unused write end
      close(d[R]); // Close unused read end of pipe 1
      dup2(d2[R], 0); // Redirect stdin to read end of pipe 2
      dup2(d[W], 1); // Redirect stdout to write end of pipe 1
      close(d2[R]); // Close read end after redirection
      close(d[W]); // Close write end after redirection

      execlp("grep", "grep", "root", NULL); // Execute grep root
      perror("execlp grep"); // Error handling if execlp fails
      _exit(1);
   }

   // Parent process (wc -l)
   close(d[W]); // Close unused write end of pipe 1
   wait(NULL); // Wait for Child 1 to finish
   dup2(d[R], 0); // Redirect stdin to read end of pipe 1
   close(d[R]); // Close read end after redirection

   execlp("wc", "wc", "-l", NULL); // Execute wc -l
   perror("execlp wc"); // Error handling if execlp fails
   return 1;
}
