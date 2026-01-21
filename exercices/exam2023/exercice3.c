#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        fprintf(stderr, "Usage: %s cmd file1 [file2 ...]\n", argv[0]);
        exit(1);
    }

    int p[2];
    if (pipe(p) == -1)
    {
        perror("pipe");
        exit(1);
    }

    if (fork() == 0)
    {
        // Child 1: cat files
        close(p[0]);         // close read end
        dup2(p[1], 1);       // redirect stdout to pipe
        close(p[1]);

        char *cat_args[argc];
        cat_args[0] = "cat";
        for (int i = 2; i < argc; i++)
            cat_args[i-1] = argv[i];
        cat_args[argc-1] = NULL;

        execv("/bin/cat", cat_args);
        perror("execv failed");
        exit(1);
    }

    if (fork() == 0)
    {
        // Child 2: cmd
        close(p[1]);         // close write end
        dup2(p[0], 0);       // redirect stdin from pipe
        close(p[0]);

        execlp(argv[1], argv[1], NULL);
        perror("execlp failed");
        exit(1);
    }

    // Parent
    close(p[0]);
    close(p[1]);
    wait(NULL);
    wait(NULL);

    return 0;
}
