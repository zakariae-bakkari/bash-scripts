#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
   int pipe1[2];
   pipe(pipe1);

   // fils 1 ls -l
   if (fork() == 0)
   {
      close(pipe1[0]);
      dup2(pipe1[1], 1);
      close(pipe1[1]);
      execlp("ls", "ls", "-l", NULL);
   }

   // fils 2 wc -l
   if (fork() == 0)
   {
      close(pipe1[1]);
      dup2(pipe1[0], 0);
      close(pipe1[0]);
      execlp("wc", "wc", "-l", NULL);
   }

   wait(NULL);
   wait(NULL);

   return 0;
}
