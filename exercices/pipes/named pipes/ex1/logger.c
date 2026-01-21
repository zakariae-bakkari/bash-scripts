#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/stat.h> // Nécessaire pour mkfifo
#include <sys/types.h>
#include <string.h>

#define FIFO_PATH "/tmp/my_log_fifo"

int main()
{
    int fd;
    char message[100];

    // 1. Création du tube nommé (FIFO)
    // Si le tube existe déjà, mkfifo renvoie -1 mais on continue
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        perror("Info: Le tube existe peut-être déjà");
    }

    printf("Logger [%d] : En attente d'un écrivain (ouverture bloquante)...\n", getpid());

    // 2. Ouverture en lecture seule (bloquant jusqu'à ce qu'un écrivain ouvre le tube)
    fd = open(FIFO_PATH, O_RDONLY);
    if (fd == -1) {
        perror("Erreur ouverture");
        return 1;
    }

    printf("Logger : Connexion établie !\n");

    // 3. Lecture en boucle
    // read renvoie 0 si l'écrivain ferme le tube (EOF)
    while (read(fd, message, sizeof(message)) > 0) 
    {
        // Condition d'arrêt
        if (strcmp(message, "exit") == 0) {
            printf("Logger : Commande exit reçue. Arrêt.\n");
            break;
        }
        printf("[LOG REÇU] : %s\n", message);
    }

    // 4. Nettoyage
    close(fd);
    unlink(FIFO_PATH); // Supprime le fichier du système
    printf("Logger : Tube supprimé.\n");
    return 0;
}