//Ejercicio6-Pr2.3 - PabloMartinez

#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>//para las funciones
#include <stdio.h>
#include <string.h>
#include <sys/types.h>

int main(){
    
    pid_t pid = fork();

    if(pid == 0){
        int pid, ppid, pgid, sid;
        rlimit noFile;
        char * dir;

        sid = setsid(); // Nueva sesion
        if(sid == -1){
            perror("Error al crear una nueva sesion");
            return EXIT_FAILURE;
        }

        if(chdir("/tmp") == -1){
            perror("Error al cambiar el directorio");
            return EXIT_FAILURE;
        }

        pid = getpid();
        ppid = getppid();
        pgid = getgid();
        dir = get_current_dir_name();

        if(getrlimit(RLIMIT_NOFILE, &noFile) == -1){
            perror("Error al obtener el numero maximo de ficheros que puede abrir");
            return EXIT_FAILURE;
        }

        sleep(5);//Dormir hijo (demonio) para que padre acabe antes

        printf("Hijo\n");
        printf("Pid: %d\n", pid);
        printf("Ppid: %d\n", ppid);
        printf("Pgid: %d\n", pgid);
        printf("Psid: %d\n", sid);
        printf("Current work directory: %s\n", dir);
    }
    else if(pid > 0) {
        sleep(10);//Dormir padre para que hijo acabe antes
        printf("Soy el proceso padre!\n");
    }
    else {
        perror("Error al hacer fork");
        return EXIT_FAILURE;
    }

    return 0;
}