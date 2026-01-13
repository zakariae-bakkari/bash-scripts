#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

void separer_commande(char commande[], char *argv[])
{
    int i = 0;

    char *token = strtok(commande, " ");
    while (token != NULL)
    {
        argv[i++] = token;  // pointeur vers commande
        token = strtok(NULL, " ");
    }
    argv[i] = NULL;
}


int main()
{
    char commande[256];
    char *argv[20]; // max 20 arguments
    pid_t pid;

    while (1)
    {
        printf("monshell> ");
        scanf(" %255[^\n]", commande);

        if (strcmp(commande, "exit") == 0)
            break;

        separer_commande(commande, argv);

        pid = fork();
        if (pid == 0)
        {
            execvp(argv[0], argv);
            perror("execvp");
            exit(1);
        }
        wait(NULL);
    }
    return 0;
}
