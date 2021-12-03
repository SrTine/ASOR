//Ejercicio4-Pr2.4 - PabloMartinez

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>

#define PATH "test.fifo"//crear el archivo¡¡¡¡

int main(int argc, char* argv[]) {
    char buf[4096];
    int fd;

    if (argc < 2) {
        fprintf(stderr, "Debe introducir un argumento\n");
        return EXIT_FAILURE;
    }

    strcpy(buf, argv[1]);
    for (int i = 2; i < argc; i++) {
        strcat(buf, " ");
        strcat(buf, argv[i]);
    }
    strcat(buf, "\n");

    fd = open(PATH, O_WRONLY);
    if(fd == -1){
        perror("Error al abrir fichero");
        return EXIT_FAILURE;
    }

    if(write(fd, buf, strlen(buf)) == -1){
        perror("Error al escribir en el fichero");
        return EXIT_FAILURE;
    }

    if(close(fd) == -1){
        perror("Error cerrar el fichero");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

