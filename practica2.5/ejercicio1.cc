//Ejercicio1-Pr2.5 - PabloMartinez

//para el getaddrinfo y el getnameinfo
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>

#include <sys/types.h>

const char *tipoToString(int ai_socktype) {
    switch (ai_socktype) {
        case SOCK_STREAM: return "Stream";
        case SOCK_DGRAM: return "Dgram";
        case SOCK_RAW: return "Raw";
        default: return "Uknown";
    }
}

const char *familiaToString(int ai_family) {
    switch (ai_family) {
        case AF_INET: return "IPv4";
        case AF_INET6: return "IPv6";
        case AF_UNSPEC: return "Both";
        default: return "Uknown";
    }
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        perror("Debe introucir una direccion IPV4/IPV6 o un nombre de dominio o un nombre e /etc/hosts valido\n");
        return EXIT_FAILURE;
    }

    char buf[64];
    int ierror;

    /*
    struct addrinfo {
               int              ai_flags;
               int              ai_family;
               int              ai_socktype;
               int              ai_protocol;
               socklen_t        ai_addrlen;
               struct sockaddr *ai_addr;
               char            *ai_canonname;
               struct addrinfo *ai_next;
           };

    */
    addrinfo hints {};
    addrinfo * res;

    for (int i = 1; i < argc; i++) {

        if ((ierror = getaddrinfo(argv[i], NULL, &hints, &res))) {// != 0 (devuelve 0 en caaso de exito y un string del fallo en caso de error)
            fprintf(stderr, "Error getaddrinfo(): %s for %s\n", gai_strerror(ierror), argv[i]);
            continue;
        }

        for (; res->ai_next; res = res->ai_next) {
            printf("%s      %s      ", argv[i], familiaToString(res->ai_family));

            if(getnameinfo(res->ai_addr, res->ai_addrlen, buf, 64, NULL, 0, NI_NUMERICHOST) != 0){
                perror("Error getnameinfo");
                return EXIT_FAILURE;
            }

            printf("%s (%s)\n", buf, tipoToString(res->ai_socktype));
        }

        freeaddrinfo(res);
    }

    return EXIT_SUCCESS;
}
