//Ejercicio13-Pr2.3 - PabloMartinez

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

volatile bool borrar = true;

static void sigUsr1Handler(int signal){
    borrar = false;
}

int main(int argc, char* argv[]) {
    int seconds;
    struct sigaction sigUsr1;

    if (argc != 2) {
        fprintf(stderr, "Debe de introducir el numero de segundos de espera antes de borrar el fichero\n");
        return EXIT_FAILURE;
    }

    seconds = atoi(argv[1]);
    
    sigUsr1.sa_handler = sigUsr1Handler;

    if(sigaction(SIGUSR1, &sigUsr1, NULL) == -1){
        perror("Error SIGINT");
        return EXIT_FAILURE;
    }

    for (int i = seconds; i > 0 && borrar; i--) {
        printf("Quedan %d segundos\n", i);
        fflush(stdout);
        sleep(1);
    }

    if (borrar) {
        if(unlink(argv[0]) == -1){
            perror("Error al borrar el ejecutable");
            return EXIT_FAILURE;
        }
        printf("Se ha borrado el programa %s\n", argv[0]);
    }else {
        printf("Se ha recibido una señal SIGUSR1 antes del tiempo especificado\n");
    }

    return EXIT_SUCCESS;
}
