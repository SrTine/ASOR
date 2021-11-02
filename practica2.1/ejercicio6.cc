//Ejercicio6-Pr2.1 - PabloMartinez

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main() {
   
   //las funciones devuelven -1 (con el errno asociado en caso de error) y el valor correspondiente en caso contrario
    if(sysconf(_SC_ARG_MAX) == -1 || sysconf(_SC_CHILD_MAX) == -1 || sysconf(_SC_OPEN_MAX) == -1 ){
       printf("%d: %s\n", errno, strerror(errno));
    }
    printf("Longitud maxima de los argumentos: %ld\n",sysconf(_SC_ARG_MAX));
    printf("Numero maximo de hijos: %ld\n",sysconf(_SC_CHILD_MAX));
    printf("Numero maximo de ficheros: %ld\n",sysconf(_SC_OPEN_MAX));

    return 0;
}