//Ejercicio2-Pr2.5 - PabloMartinez

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string>

/*
La dirección y el puerto son el primer y segundo argumento del programa. Las direcciones pueden expresarse en cualquier formato (nombre de host, notación de punto…). Además, el servidor debe funcionar con direcciones IPv4 e IPv6 .
El servidor recibirá un comando (codificado en un carácter), de forma que ‘t’ devuelva la hora, ‘d’ devuelve la fecha y ‘q’ termina el proceso servidor.
En cada mensaje el servidor debe imprimir el nombre y puerto del cliente, usar getnameinfo(3).
*/

#define TIME_REPR "%X"
#define DATE_REPR "%x"

int main(int argc, char* argv[]) {
    addrinfo hints {};
    addrinfo * res;
    sockaddr_storage caddr;
    socklen_t caddrlen;
    bool running = true;
    size_t size, msgsize;
    time_t t;
    tm * tm;
    int ierror, sd;
    char buf[64], bufserv[64], bufhost[64], timebuf[64];

    if (argc < 3) {
        perror("Debe introcudir la direccion y el puerto\n");
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

    if(bind(sd, res->ai_addr, res->ai_addrlen) == -1){
        perror("Error en el bind");
        return EXIT_FAILURE;
    }

    printf("Server listening on %s:%s\n", bufhost, bufserv);
    while (running) {
        caddrlen = sizeof(caddr);
        size = recvfrom(sd, buf, 64, 0, (sockaddr*)&caddr, &caddrlen);
        if(size == -1){
            perror("Error al recibir del cliente\n");
            return EXIT_FAILURE;
        }
        getnameinfo((sockaddr *)&caddr, caddrlen, bufhost, 64, bufserv, 64, 0);
        printf("%ld bytes de [%s]:%s\n", size, bufhost, bufserv);

        t = time(NULL);
        tm = localtime(&t);

        switch (buf[0]) {
            case 't':
                size = strftime(timebuf, 64, TIME_REPR, tm);
                if(sendto(sd, timebuf, size, 0, (sockaddr*) &caddr, caddrlen) == -1){
                    perror("Error al enviar al cliente (t)\n");
                    return EXIT_FAILURE;
                }
                break;
            case 'd':
                size = strftime(timebuf, 64, DATE_REPR, tm);
                if(sendto(sd, timebuf, size, 0, (sockaddr*) &caddr, caddrlen) == -1){
                    perror("Error al enviar al cliente (d)\n");
                    return EXIT_FAILURE;
                }
                break;
            case 'q': printf("Conexion cerrada\n");running = false; break;
            case '\n': break;
            default: fprintf(stderr, "Debe introducir t , d ó q: %c\n", buf[0]); break;
        }
    }

    if(close(sd) == -1){
        perror("Error en el close");
        return EXIT_FAILURE;
    }
    freeaddrinfo(res);

    return EXIT_SUCCESS;
}