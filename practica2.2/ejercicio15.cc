//Ejercicio15-Pr2.2 - PabloMartinez -- hecho
#include <stdio.h>
#include <unistd.h>//para la funcion lockf
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <time.h>//para la funcion sleep

#define SLEEP_TIME 30

int main(int argc, char ** argv) {
    int fd;
    char* fname;

   if (argc > 1){
        fname = argv[1];
    }
    else{
        perror("Debe introducir por argumento un fichero");
        return EXIT_FAILURE;
    }

    fd = open(argv[1], O_WRONLY);

    if(fd == -1){
        perror("Error al abrir el fichero");
        return EXIT_FAILURE;
    }

    if (lockf(fd, F_TEST, 0) == 0) {//testea si el fichero ya esta bloqueado por otro proceso (0 si exito y -1 si error)
        if(lockf(fd, F_LOCK, 0) == -1){//lo bloqueamos (libera el cerrojo anterior si habia)
            perror("Error al bloquear el cerrojo del fichero");
            return EXIT_FAILURE;
        }
        else{
            printf("Cerrojo bloqueado\n");
            time_t t = time(0);
            struct tm *lt = localtime(&t);

            printf("Hora %d:%d\n", lt->tm_hour, lt->tm_min);//escribimos la hora

            printf("Durmiendo durante 30 segundos...\n");
            sleep(30);//dormimos durante 30 seg

            if(lockf(fd, F_ULOCK, 0) == -1){//lo desbloqueamos
                perror("Error al desbloquear el cerrojo del fichero");
                return EXIT_FAILURE;
            }
            printf("Cerrojo desbloqueado\n");
        }
    }
    else{
        perror("Bloqueado por otro proceso\n");
        return EXIT_FAILURE;
    }

    return 0;
}