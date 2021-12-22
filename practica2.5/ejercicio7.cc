//Ejercicio7-Pr2.5 - PabloMartinez

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

int main(int argc, char* argv[]) {
    addrinfo hints {};
    addrinfo * res;
    bool running = true;
    size_t size;
    int ierror, sd;
    char bufserv[64], bufhost[64];
    char * line;

    if(argc != 3) {
        perror("Debe introcudir la direccion y el puerto\n");
        return EXIT_FAILURE;
    }

    hints.ai_socktype = SOCK_STREAM;

    ierror = getaddrinfo(argv[1], argv[2], &hints, &res);

    if(ierror != 0) {
        perror("Error en el getaddrinfo");
        return EXIT_FAILURE;
    }

    if(getnameinfo(res->ai_addr, res->ai_addrlen, bufhost, 64, bufserv, 64, NI_NUMERICHOST | NI_NUMERICSERV) != 0){
        perror("Error en el getnameinfo");
        return EXIT_FAILURE;
    }
    
    sd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if(sd == -1){
        perror("Error en el socket");
        return EXIT_FAILURE;
    }
    
    if(connect(sd, res->ai_addr, res->ai_addrlen) == -1){
        perror("Error en el connect");
        return EXIT_FAILURE;
    }

    printf("Connected to [%s]:%s\n", bufhost, bufserv);
    while (running) {
        size = 0;
        line = NULL;
        size = getline(&line, &size, stdin);
        if(size == -1){
            perror("Error en el getline\n");
            return EXIT_FAILURE;
        }

        if (size == 2 && line[0] == 'Q') {
            running = false;
        } else {
            if(send(sd, line, size, 0) == -1){
                perror("Error en el send\n");
                return EXIT_FAILURE;
            }
            if(recv(sd, line, size, 0) == -1){
                perror("Error en el recv\n");
                return EXIT_FAILURE;
            }
            fputs(line, stdout);
        }

        free(line);
    }

    if(close(sd) == -1){
        perror("Error en el close");
        return EXIT_FAILURE;
    }

    freeaddrinfo(res);

    return EXIT_SUCCESS;
}
