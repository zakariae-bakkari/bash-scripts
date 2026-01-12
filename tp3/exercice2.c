#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
void afficher_infos()
{
  printf("PID  : %d\n", getpid());
  printf("PPID : %d\n", getppid());
  printf("UID  : %d (EUID: %d)\n", getuid(), geteuid());
  printf("GID  : %d (EGID: %d)\n", getgid(), getegid());
}

int main()
{
  pid_t p;

  p = fork(); // f1

  if (p < 0)
  {
    printf("Fork failed");
    exit(-1);
  }

  if (p == 0)
  { // fils 1
    printf("Processus fils:\n");
    afficher_infos();
  }
  else
  {
    wait(NULL);
    printf("Processus pere:\n");
    afficher_infos();
  }

  return 0;
}