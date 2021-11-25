//Ejercicio5-Pr2.3 - PabloMartinez

#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>//para las funciones
#include <stdio.h>
#include <string.h>


int main() {
    int pid, ppid, pgid, sid;
    rlimit noFile;
    char * dir;

    pid = getpid();
    ppid = getppid();
    pgid = getpgid(pid);
    sid = getsid(pid);
    dir = get_current_dir_name();

    if(getrlimit(RLIMIT_NOFILE, &noFile) == -1){
        perror("Error al obtener el numero maximo de ficheros que puede abrir");
        return EXIT_FAILURE;
    }

    printf("Pid: %d\n", pid);
    printf("Ppid: %d\n", ppid);
    printf("Pgid: %d\n", pgid);
    printf("Psid: %d\n", sid);
    printf("Max files opened: %ld\n", noFile.rlim_cur);
    printf("Current work directory: %s\n", dir);

    return EXIT_SUCCESS;
}
