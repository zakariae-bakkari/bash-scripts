#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

int count = 0; // global variable

static void action(int sig)
{
   ++count;
   write(1, "capture du signal SIGINT\n", 26);
}

static void action2(int sig)
{
   ++count;
   write(1, "capture du signal quit\n", 24);
}

int main()
{
   if (fork() == 0)
   {
      sleep(16);
   }

   while (1)
   {
      printf("Travail en cours... (count=%d)\n", ++count);
      sleep(1);
   }
   
   
   return 0;
}