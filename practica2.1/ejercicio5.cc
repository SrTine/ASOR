//Ejercicio5-Pr2.1 - PabloMartinez

//El ejercicio 4 es para comprobar por consola que la información del sistema coincide con la que genera este programa

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/utsname.h>

int main() {
    //estructura que recoge la información de uname
    utsname info;

    //la funcion uname devuelve 0 en caso de exito y -1 en caso de error (con el errno asociado)
    if (uname(&info)) {
        printf("%d: %s\n", errno, strerror(errno));
    }

    printf("%s %s %s %s %s %s\n",info.sysname,info.nodename,info.release,info.version,info.machine,info.domainname);

    return 0;
}