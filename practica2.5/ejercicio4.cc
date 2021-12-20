//Ejercicio4-Pr2.5 - PabloMartinez

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string>

#define TIME_REPR "%X"
#define DATE_REPR "%x"

int main(int argc, char* argv[]) {
    addrinfo hints {};
    addrinfo * res;
    sockaddr_storage caddr;
    socklen_t caddrlen;
    bool running = true, response;
    size_t size;
    fd_set set;
    time_t t;
    tm * tm;
    int ierror, sd, nfds;
    char * chptr;
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

    FD_ZERO(&set);

    printf("Server listening on %s:%s\n", bufhost, bufserv);
    while (running) {
        FD_SET(sd, &set);
        FD_SET(fileno(stdin), &set);

        nfds = select(sd+1, &set, NULL, NULL, NULL);

        if(nfds == -1){
            perror("Error en el select");
            return EXIT_FAILURE;
        }

        for (int i = 0; i < nfds; i++) {
            
            if (FD_ISSET(sd, &set)) {
                caddrlen = sizeof(caddr);

                size = recvfrom(sd, buf, 64, 0, (sockaddr*)&caddr, &caddrlen);
                if(size == -1){
                    perror("Error al recibir del cliente\n");
                    return EXIT_FAILURE;
                }
                getnameinfo((sockaddr *)&caddr, caddrlen, bufhost, 64, bufserv, 64, 0);

                printf("%ld bytes de [%s]:%s\n", size, bufhost, bufserv);
            }else if (FD_ISSET(fileno(stdin), &set)) {
                fgets(buf, 64, stdin);
            }

            t = time(NULL);
            tm = localtime(&t);
            response = false;

            switch (buf[0]) {
                case 't':
                    strftime(timebuf, 64, TIME_REPR, tm);
                    response = true;
                    break;
                case 'd':
                    strftime(timebuf, 64, DATE_REPR, tm);
                    response = true;
                    break;
                case 'q':  printf("Conexion cerrada\n");running = false; break;
                case '\n': break;
                default: fprintf(stderr, "Debe introducir t , d ó q: %c\n", buf[0]); break;
            }

            
            if (FD_ISSET(sd, &set) && response) {
                if(sendto(sd, timebuf, 64, 0, (sockaddr*) &caddr, caddrlen) == -1){
                    perror("Error al enviar al cliente\n");
                    return EXIT_FAILURE;
                }

                FD_CLR(sd, &set);
            } else if (FD_ISSET(fileno(stdin), &set) && response) {
                printf("%s\n", timebuf);

                FD_CLR(sd, &set);
            }
        }

    }

    if(close(sd) == -1){
        perror("Error en el close");
        return EXIT_FAILURE;
    }
    
    freeaddrinfo(res);

    return EXIT_SUCCESS;
}
