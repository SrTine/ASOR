//Ejercicio9-Pr2.1 - PabloMartinez
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main() {
    int uid, euid;
    uid = getuid();//returns the real user ID of the calling process
    euid = geteuid();//returns the effective user ID of the calling process

    if (uid == -1 || euid == -1){
        printf("%d: %s\n", errno, strerror(errno));
    }

    printf("UID real: %ld\n",uid);
    printf("UID efectivo: %ld\n",euid);

    if (euid != uid) {
        fprintf(stderr, "Setuid used");
    }

    return 0;
}
