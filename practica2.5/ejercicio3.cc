//Ejercicio3-Pr2.5 - PabloMartinez

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string>

int main(int argc, char* argv[]) {
    addrinfo hints {};
    addrinfo * res;
    size_t size;
    int ierror, sd;
    char buf[64], bufserv[64], bufhost[64];

    if (argc != 4) {
        perror("Debe introducir la direccion y el puerto del servidor y la hora\n");
        return EXIT_FAILURE;
    }

    if ((argv[3][0] != 'd' && argv[3][0] != 't' && argv[3][0] != 'q')) {
        perror("Comando no existente, debe introducir t , d ó q\n");
        return EXIT_FAILURE;
    }

    hints.ai_socktype = SOCK_DGRAM;

    ierror = getaddrinfo(argv[1], argv[2], &hints, &res);
    if (ierror != 0) {
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

    printf("Sending to %s:%s\n", bufhost, bufserv);

    if(sendto(sd, argv[3], 64, 0, res->ai_addr, res->ai_addrlen) == -1){
        perror("Error al enviar al servidor\n");
        return EXIT_FAILURE;
    }

    if (argv[3][0] != 'q') {
        size = recvfrom(sd, buf, 64, 0, NULL, NULL);
        
        if(size == -1){
            perror("Error al recibir del servidor\n");
            return EXIT_FAILURE;
        }
        printf("%s\n", buf);
    }

    if(close(sd) == -1){
        perror("Error en el close");
        return EXIT_FAILURE;
    }

    freeaddrinfo(res);

    return EXIT_SUCCESS;
}
