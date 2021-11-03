//Ejercicio13-Pr2.1 - PabloMartinez

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>

int main() {
    timeval tIni, tFin;//estructura para guardar el resultado de la funcion gettimeofday
    int total;//para guardar el resultado (podria ser tmbn suseconds_t)
    int var = 0;

    if(gettimeofday(&tIni, NULL) != 0){
         printf("%d: %s\n", errno, strerror(errno));
    }
    for (int i = 0; i < 10000000; i++) {
        var++;
    }
   if(gettimeofday(&tFin, NULL) != 0){
         printf("%d: %s\n", errno, strerror(errno));
    }

    total = tFin.tv_usec - tIni.tv_usec;

    printf("Total: %ld microsegundos\n", total);

    return 0;
}
