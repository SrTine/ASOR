//Ejercicio12-Pr2.3 - PabloMartinez

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <signal.h>

volatile unsigned int nInt = 0;
volatile unsigned int nStp = 0;

static void sigIntHandler(int signal){
    nInt = nInt + 1;
}

static void sigtStpHandler(int signal){
    nStp = nStp + 1;
}

int main(int argc, char* argv[]) {
    struct sigaction sigInt;
    struct sigaction sigtStp;

    sigInt.sa_handler = sigIntHandler;
    sigtStp.sa_handler = sigtStpHandler;

    if(sigaction(SIGINT, &sigInt, NULL) == -1){
        perror("Error SIGINT");
        return EXIT_FAILURE;
    }

    if(sigaction(SIGTSTP, &sigtStp, NULL) == -1){
        perror("Error SIGSTP");
        return EXIT_FAILURE;
    }

    while (nInt + nStp < 10) {
        printf("Numero de SIGINT: %d\n", nInt);
        printf("Numero de SIGSTP: %d\n\n", nStp);
    } 
    
    printf("Progama termino su ejecuccion\n");
    printf("Numero de SIGINT: %d\n", nInt);
    printf("Numero de SIGSTP: %d\n", nStp);

    return EXIT_SUCCESS;
}
