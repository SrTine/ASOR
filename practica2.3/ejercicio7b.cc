//Ejercicio7.b-Pr2.3 - PabloMartinez

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

//version con exec - no se eecuta el printf porque el execv sustituye el codigo del programa
int main(int argc, char* argv[]) {
 if (argc < 2) {
        fprintf(stderr, "Introduce un comando\n");
        return EXIT_FAILURE;
    }

    if(execvp(argv[1], &argv[1]) == -1){
        perror("Error al ejecutar el comando");
        return EXIT_FAILURE;
    }

    printf("El comando terminó de ejecutarse\n");

    return EXIT_SUCCESS;
}
