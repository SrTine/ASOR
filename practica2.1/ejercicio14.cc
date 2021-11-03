//Ejercicio14-Pr2.1 - PabloMartinez

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

int main() {
    time_t t;
    tm * tm;//puntero a estructura para guardar lo que devuelve localtime

    t = time(NULL);

    if(t == -1){
        printf("%d: %s\n", errno, strerror(errno));
    }

    tm = localtime(&t);

    if (tm == NULL){
         printf("%d: %s\n", errno, strerror(errno));
    }

    printf("Anio: %d\n", tm->tm_year+1900);//le sumamos 1900 porque es el Epoch (si noo devuelve cuantos anios han pasado desde 1900)

    return 0;
}
