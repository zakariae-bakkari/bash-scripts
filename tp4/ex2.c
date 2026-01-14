#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    int pipe1[2]; // Entre ps et grep
    int pipe2[2]; // Entre grep et wc

    pipe(pipe1); // Création tube 1 [cite: 544]
    
    if (fork() == 0) {
        // --- Processus 1 : ps -aux ---
        // Redirige stdout vers l'entrée du pipe1
        dup2(pipe1[1], STDOUT_FILENO);
        
        // Ferme les descripteurs inutiles (Très important pour éviter les blocages !) [cite: 653]
        close(pipe1[0]); 
        close(pipe1[1]);
        
        execlp("ps", "ps", "-aux", NULL);
        perror("Echec ps"); exit(1);
    }

    pipe(pipe2); // Création tube 2

    if (fork() == 0) {
        // --- Processus 2 : grep root ---
        // Lit depuis pipe1
        dup2(pipe1[0], STDIN_FILENO);
        // Ecrit vers pipe2
        dup2(pipe2[1], STDOUT_FILENO);
        
        // Fermeture propre
        close(pipe1[0]); close(pipe1[1]);
        close(pipe2[0]); close(pipe2[1]);
        
        execlp("grep", "grep", "root", NULL);
        perror("Echec grep"); exit(1);
    }

    // Fermeture des descripteurs du pipe1 dans le père pour que grep reçoive EOF
    close(pipe1[0]);
    close(pipe1[1]);

    if (fork() == 0) {
        // --- Processus 3 : wc -l ---
        // Lit depuis pipe2
        dup2(pipe2[0], STDIN_FILENO);
        
        close(pipe2[0]); close(pipe2[1]);
        
        execlp("wc", "wc", "-l", NULL);
        perror("Echec wc"); exit(1);
    }

    // Le père ferme tout et attend
    close(pipe2[0]);
    close(pipe2[1]);
    
    // Attente des 3 fils
    wait(NULL); wait(NULL); wait(NULL);
    
    return 0;
}