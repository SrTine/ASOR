//Ejercicio11-Pr2.2 - PabloMartinez --hecho
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>//para la funcion link y symlink
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

#define MAX_STR 4096

int main(int argc, char *argv[]){
    char* fname;
    struct stat st;

    if (argc > 1){
        fname = argv[1];
    }
    else{
        perror("Debe introducir por argumento un fichero");
        return EXIT_FAILURE;
    }

    if(stat(fname, &st) == -1){
        perror("Error al guardar info en estructura stat");
        return EXIT_FAILURE;
    }

    if(S_ISREG(st.st_mode)) {//solo si es un fichero regular
        char fnamehlink[MAX_STR];
        char fnameslink[MAX_STR];

        strcat(strcpy(fnamehlink, fname), ".hard");
        strcat(strcpy(fnameslink, fname), ".sym");

        //comprobamos que se han realizado los enlaces
        if(link(fname, fnamehlink) == -1){//devuelve 0 en caso de exito y -1 en caso de error
            perror("Error al crear  enlace rigido");
        }
        if(symlink(fname, fnameslink) == -1){//devuelve 0 en caso de exito y -1 en caso de error
            perror("Error al crear enlace simbolico");
        }
    }

    return 0;
}
