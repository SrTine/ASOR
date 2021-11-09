//Ejercicio5-Pr2.2 - PabloMartinez -- hecho

#include <stdio.h>
#include <stdlib.h>//para macro EXIT_FAILURE
#include <sys/types.h>//libreria para open
#include <sys/stat.h>//libreria para open
#include <errno.h>
#include <string.h>
#include <fcntl.h>//libreria para open

int main(int argc, char ** argv) {
    char* fname;

     if (argc > 1) {//si pasa el nombre del fichero por argumento
        fname = argv[1];
    }
    else {//si no le asignamos un nombre por defecto (Si el fichero existe lo truncamos)
        fname = "fichero";
    }

	//permisos rw-r--r-x (645)
   	if(open(fname, O_CREAT | O_WRONLY | O_TRUNC, 00645) == -1){//devuelve el fd del fichero o -1 en caso de error
		perror("Error al abrir el fichero");
        return EXIT_FAILURE;
	}

    return 0;
}
