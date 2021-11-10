//Ejercicio13-Pr2.2 - PabloMartinez -- hecho
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]){
    int fd;
    char* fname;

    if (argc > 1){
        fname = argv[1];
    }
    else{
        perror("Debe introducir por argumento un fichero");
        return EXIT_FAILURE;
    }

    fd = open(argv[1], O_WRONLY | O_CREAT, 00666);

    if(fd == -1){
        perror("Error al abrir el fichero");
        return EXIT_FAILURE;
    }

    if(dup2(fd, STDOUT_FILENO) == -1){
        perror("Error al redirigir la salida estandar");
        return EXIT_FAILURE;
    }

    if(dup2(fd, STDERR_FILENO) == -1){
        perror("Error al redirigir la salida estandar de error");
        return EXIT_FAILURE;
    }

    //Es importante el orden
        //si redireccionamos stderr a stdout antes que stdout a fichero, no escribira en el fichero

    //pruebas
    printf("Hello World \n");//escribe en fichero
    fprintf(stdout, "Hello World\n");//escribe en fichero
    fprintf(stderr, "Hello World\n");//escribe en fichero

    return 0;
}

  