//Ejercicio15-Pr2.1 - PabloMartinez

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <time.h>
#include <locale.h>

int main(){
    tm *tm;
    time_t t;

    char s[255];//establecemos un tamanio maximo de 255 bytes
    
    setlocale(LC_ALL, "es_ES");//configuracion regional

    t = time(NULL);

    if(t == -1){
       printf("%d: %s\n", errno, strerror(errno));
    }

    tm = localtime(&t);

    if(tm == NULL){
        printf("%d: %s\n", errno, strerror(errno));
    }

    int res = strftime(s, sizeof(s), "%A, %e de %B de %Y, %H:%M", tm);//formato legible decidido

    if(res == 255 || res == -1){//-1 en caso de fallo o tamanio maximo buffer si no cabe
        printf("%d: %s\n", errno, strerror(errno));
    }

    printf("%s\n", s);

    return 0;
}