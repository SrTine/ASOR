//Ejercicio6-Pr2.5 - PabloMartinez

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

#define DEFAULT_BACKLOG 10

int main(int argc, char* argv[]) {
    addrinfo hints {};
    addrinfo * res;
    sockaddr_storage caddr;
    socklen_t caddrlen;
    bool running = true;
    size_t size;
    int ierror, sd, csd;
    char buf[64], bufserv[64], bufhost[64];

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

    if(bind(sd, res->ai_addr, res->ai_addrlen) == -1){
        perror("Error en el bind");
        return EXIT_FAILURE;
    }

    if(listen(sd, DEFAULT_BACKLOG) == -1){
        perror("Error en el listen");
        return EXIT_FAILURE;
    }

    printf("Server listening on %s:%s\n", bufhost, bufserv);
    while (running) {
        caddrlen = sizeof(caddr);
        csd = accept(sd, (sockaddr*)&caddr, &caddrlen);
        
        if(csd == -1){
            perror("Error en el accept");
            return EXIT_FAILURE;
        }

        getnameinfo((sockaddr *)&caddr, caddrlen, bufhost, 64, bufserv, 64, 0);
        printf("Conexión desde [%s]:%s\n", bufhost, bufserv);

        while (true) {
            size = recv(csd, buf, 64, 0);
            if(size == -1){
                perror("Error en el recv\n");
                return EXIT_FAILURE;
            }else if (size == 0) break; // Conexión terminada

            if(send(csd, buf, size, 0) == -1){
                perror("Error en el send\n");
                return EXIT_FAILURE;
            }
        }

        printf("Terminada conexión de [%s]:%s\n", bufhost, bufserv);
        if(close(csd) == -1){
            perror("Error en el close cliente");
            return EXIT_FAILURE;
        }
    }

    if(close(sd) == -1){
        perror("Error en el close");
        return EXIT_FAILURE;
    }

    freeaddrinfo(res);

    return EXIT_SUCCESS;
}
