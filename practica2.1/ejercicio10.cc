//Ejercicio10-Pr2.1 - PabloMartinez
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>


int main() {
    int uid, euid;
    uid = getuid();//returns the real user ID of the calling process
    euid = geteuid();//returns the effective user ID of the calling process
    passwd * passwd;//puntero a estructura donde se guarda la informacion de getpwuid

    if (uid == -1 || euid == -1){
        printf("%d: %s\n", errno, strerror(errno));
    }

    printf("UID real: %ld\n",uid);
    printf("UID efectivo: %ld\n",euid);

    if (euid != uid) {
        fprintf(stderr, "Setuid used");
    }

    passwd = getpwuid(uid);

    if(passwd == NULL){
        printf("%d: %s\n", errno, strerror(errno));
    }

    printf("Nombre usuario: %s\n", passwd->pw_name);
    printf("Directorio home: %s\n", passwd->pw_dir);
    printf("Descripcion del usuario: %s\n", passwd->pw_gecos);

    return 0;
}