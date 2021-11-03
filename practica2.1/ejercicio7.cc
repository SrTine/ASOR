//Ejercicio7-Pr2.1 - PabloMartinez

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main() {

     //las funciones devuelven -1 (con el errno asociado en caso de error) y el valor correspondiente en caso contrario
    if(pathconf(".", _PC_LINK_MAX) == -1 || pathconf(".", _PC_PATH_MAX) == -1 || pathconf(".", _PC_NAME_MAX) == -1 ){
       printf("%d: %s\n", errno, strerror(errno));
    }

    printf("Numero maximo de enlaces: %ld\n",pathconf(".", _PC_LINK_MAX));
    printf("Tamano maximo de ruta: %ld\n",pathconf(".", _PC_PATH_MAX));
    printf("Tamano maximo nombre fichero: %ld\n",pathconf(".", _PC_NAME_MAX));

    return 0;
}