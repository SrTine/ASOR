//Ejercicio12-Pr2.1 - PabloMartinez
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>

int main() {
    time_t t;

    t = time(NULL);//returns the time as the number of seconds since the Epoch

    if(t == -1){
         printf("%d: %s\n", errno, strerror(errno));
    }

    printf("%ld\n", t);

    return 0;
}
