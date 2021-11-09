//Ejercicio7-Pr2.2 - PabloMartinez -- hecho
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>//para el open y el umask
#include <sys/stat.h>//para el open y el umask
#include <errno.h>
#include <string.h>
#include <fcntl.h>

int main(int argc, char ** argv) {
    char * fname;

    if (argc > 1) {
        fname = argv[1];
    }
    else {
        fname = "fichero";
    }
   
    //como ~00645 = 03 -> la funcion debe devolver 2
    if(umask(~00645) != 2){//retorna el valor previo de la mascara
        perror("Error al fijar las mascara");
        return EXIT_FAILURE;
    }
    
    if(open(fname, O_CREAT | O_WRONLY| O_TRUNC, 00645) == -1){
        perror("Error al abrir el fichero");
        return EXIT_FAILURE;
    }

    return 0;
}
