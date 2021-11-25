//Ejercicio7.a-Pr2.3 - PabloMartinez

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

//version con system -  en esta version si se ejecuta el printf
int main(int argc, char* argv[]) {

    if (argc < 2) {
        fprintf(stderr, "Introduce un comando\n");
        return EXIT_FAILURE;
    }

    if(system(argv[1]) == -1){
        perror("Error al ejecutar el comando");
        return EXIT_FAILURE;
    }

    printf("El comando terminó de ejecutarse\n");

    return 0;
}
