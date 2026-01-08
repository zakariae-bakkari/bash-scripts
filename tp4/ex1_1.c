#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
   if (fork() == 0)
   {
      printf("Processus fils : \n");
      for (int i = 1; i <= 100; i++)
      {
         // impaire
         if (i % 2 != 0)
            printf("%d \n", i);
         
      }
      
   }else {
      wait(NULL);
      printf("Processus pere : \n");
      for (int i = 1; i <= 100; i++)
      {
         // paire
         if (i % 2 == 0)
            printf("%d \n", i);
         
      }
   }
   
}