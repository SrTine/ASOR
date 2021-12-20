//Ejercicio5-Pr2.5 - PabloMartinez

#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>

#define TIME_REPR "%X"
#define DATE_REPR "%x"

void server(int sd) {
    char buf[64], timebuf[64], bufhost[64], bufserv[64];
    sockaddr_storage caddr;
    socklen_t caddrlen;
    size_t size;
    time_t t;
    tm * tm;
    bool running = true;

    printf("Created thread pid: %d, gpid: %d\n", getpid(), getpgid(0));
    while(running) {
        caddrlen = sizeof(caddr);

        size = recvfrom(sd, buf, 64, 0, (sockaddr*)&caddr, &caddrlen);
        if(size == -1){
            perror("Error al recibir del cliente\n");
            exit(EXIT_FAILURE);
        } 

        getnameinfo((sockaddr *)&caddr, caddrlen, bufhost, 64, bufserv, 64, 0);
        printf("%ld bytes de [%s]:%s at pid %d\n", size, bufhost, bufserv, getpid());

        t = time(NULL);
        tm = localtime(&t);

        switch(buf[0]) {
            case 't':
                strftime(timebuf, 64, TIME_REPR, tm);
                if(sendto(sd, timebuf, strlen(timebuf), 0, (sockaddr*) &caddr, caddrlen) == -1){
                    perror("Error al enviar al cliente t\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'd':
                strftime(timebuf, 64, DATE_REPR, tm);
                if(sendto(sd, timebuf, strlen(timebuf), 0, (sockaddr*) &caddr, caddrlen) == -1){
                    perror("Error al enviar al cliente d\n");
                    exit(EXIT_FAILURE);
                }
                break;
            case 'q':  printf("Conexion cerrada\n");running = false; break;
            case '\n': break;
            default: fprintf(stderr, "Debe introducir t , d ó q: %c\n", buf[0]); break;
        }
    }

    exit(EXIT_SUCCESS);
}

int main(int argc, char* argv[]) {
    addrinfo hints {};
    addrinfo * res;
    int ierror, sd, nproc;
    pid_t gpid = 0, pid = 0;
    char bufserv[64], bufhost[64];

    if(argc != 4) {
        perror("Debe introcudir la direccion, el puerto y el num de procesos\n");
        return EXIT_FAILURE;
    }

    nproc = atoi(argv[3]);
    hints.ai_socktype = SOCK_DGRAM;

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

    printf("Server listening on %s:%s\n", bufhost, bufserv);


    for(int i = 0; i < nproc; i++) {
        pid = fork();

        if(pid == -1){
            perror("Error al crear un proceso");
            return EXIT_FAILURE;
        }else if(pid == 0) {

            if(setpgid(0, gpid) == -1){
                perror("Error al setear pgid");
                return EXIT_FAILURE;
            }
            server(sd);
            exit(EXIT_FAILURE);
        }else if(i == 0) {
            gpid = pid;
        }
    }

    if(pid) {
        //esperamos a que uno de los hijos acabe
        if(wait(&ierror) == -1){
            perror("Error al esperar a uno de los hijos");
            return EXIT_FAILURE;
        }
        
        if (ierror != EXIT_SUCCESS) {
            perror("Uno de los hijos ha fallado");
            return EXIT_FAILURE;
        }

        printf("Uno de los hijos a muerto\n");

        //matamos el resto de procesos
        kill(-gpid, SIGTERM);

        for (int i = 0; i < nproc-1; i++) {
            if(wait(NULL) == -1){
                perror("Error esperar a los hijos");
                return EXIT_FAILURE;
            }
        }

        if(close(sd) == -1){
            perror("Error en el close");
            return EXIT_FAILURE;
        }

        freeaddrinfo(res);
    }

    return EXIT_SUCCESS;
}
