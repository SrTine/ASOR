//Ejercicio5-Pr2.4 - PabloMartinez

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>

int main(int argc, char* argv[]) {
    char buf[256];
    size_t size;
    int maxfd;
    int retVal;
    fd_set rfds;

    int fd1 = open("pipe1", O_RDONLY | O_NONBLOCK);
    int fd2 = open("pipe2", O_RDONLY | O_NONBLOCK);

    int maxfd = fd1 > fd2 ? fd1 : fd2;

    if(fd1 == -1){
        perror("pipe1 open error");
        return EXIT_FAILURE;
    }
    if(fd2 == -1){
        perror("pipe2 open error");
        return EXIT_FAILURE;
    }

    FD_ZERO(&rfds);

    //Abrimos las tuberías
    FD_SET(fd1, &rfds);
    FD_SET(fd2, &rfds);

    while (true) {
      retVal = select(maxfd + 1, &rfds, NULL, NULL, NULL);

        if(retVal == -1){
            perror("Error en el select");
            return EXIT_FAILURE;
        }
        else if(retVal){
            if(FD_ISSET(fd1, &rfds)){
                retVal = read(fd1, buf, sizeof(buf));

                if(retVal == -1){
                    perror("Error al leer en pipe1");
                    return EXIT_FAILURE;
                }

                else if (retVal == 0){//fin del fichero (cerrar y volver a abrir) 
                    if(close(fd1) == -1){
                        perror("Error al cerrar pipe1");
                        return EXIT_FAILURE;
                    }

                    fd1 = open("pipe1", O_RDONLY | O_NONBLOCK);
                }

                else{
                    printf("Leido de pipe1: %s\n", buf);
                }
            }
            else if(FD_ISSET(fd2, &rfds)){
                retVal = read(fd2, buf, sizeof(buf));

                if(retVal == -1){
                    perror("Error al leer en pipe2");
                    return EXIT_FAILURE;
                }

                else if (retVal == 0){//fin del fichero (cerrar y volver a abrir) 
                    if(close(fd2) == -1){
                        perror("Error al cerrar pipe2");
                        return EXIT_FAILURE;
                    }

                    fd2 = open("pipe2", O_RDONLY | O_NONBLOCK);
                }

                else{
                    printf("Leido de pipe2: %s\n", buf);
                }
            }
        }
    }
    
    return EXIT_SUCCESS;
}

