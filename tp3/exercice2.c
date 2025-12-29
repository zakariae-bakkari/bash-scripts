#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t p;

    p = fork();//f1

    if (p == 0) { // fils 1
      printf("Processus fils:\n");
      printf("PID: %d\n", getpid());
      printf("PPID: %d\n", getppid());
      printf("UID: %d\n", getuid());
      printf("EUID: %d\n", geteuid());
      printf("GID: %d\n", getgid());
      printf("EGID: %d\n", getegid());
    }else{
      printf("Processus pere:\n");
      printf("PID: %d\n", getpid());
      printf("PPID: %d\n", getppid());
      printf("UID: %d\n", getuid());
      printf("EUID: %d\n", geteuid());
      printf("GID: %d\n", getgid());
      printf("EGID: %d\n", getegid());
    }

    return 0;
}