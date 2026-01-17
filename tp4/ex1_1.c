#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

// Variables globales pour la synchronisation
pid_t pid_fils = 0;

// Handler qui ne fait rien, juste pour interrompre le pause()
void handler(int sig) {
    return;
}

int main() {
    pid_t pid;
    
    // Installation du gestionnaire de signal
    signal(SIGUSR1, handler);

    if ((pid = fork()) == 0) {
        // --- Code du FILS (Impairs) ---
        for (int i = 1; i < 100; i += 2) {
            printf("%d ", i);
            fflush(stdout);// fflush pour s'assurer que la sortie est immédiate
            
            // Envoie le signal au père (le père est le PPID du fils)
            kill(getppid(), SIGUSR1);
            
            // Attend le signal du père pour continuer
            if (i < 99) pause(); 
        }
        exit(0);
    } else {
        // --- Code du PÈRE (Pairs) ---
        // Le père attend le premier signal du fils (qui commence avec 1)
        pause();
        
        for (int i = 2; i <= 100; i += 2) {
            printf("%d ", i);
            fflush(stdout);
            
            // Envoie le signal au fils
            kill(pid, SIGUSR1);
            
            // Attend le signal du fils pour continuer
            if (i < 100) pause();
        }
    }
    printf("\n");
    return 0;
}