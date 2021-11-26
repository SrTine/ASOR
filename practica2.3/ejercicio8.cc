//Ejercicio8-Pr2.3 - PabloMartinez

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    pid_t pid;
    int fdi, fdo, fde;

    if (argc < 2) {
        fprintf(stderr, "Introduce un comando\n");
        return EXIT_FAILURE;
    }
    
    pid = fork();
    if (pid == 0) {
        if(chdir("/tmp") == -1){
            perror("Error al cambiar el directorio");
            return EXIT_FAILURE;
        }

        if(fdi = open("/dev/null", O_RDONLY, 0777) == -1){
            perror("Error al crear la entrada estandar");
            return EXIT_FAILURE;
        }

        if(fdo = open("daemon.out", O_WRONLY | O_CREAT | O_TRUNC , 0777) == -1){
            perror("Error al crear la salida estandar");
            return EXIT_FAILURE;
        }

        if(fde = open("daemon.err", O_WRONLY | O_CREAT | O_TRUNC, 0777) == -1){
            perror("Error al crear la salida de error estandar");
            return EXIT_FAILURE;
        }

        if(dup2(fdi, fileno(stdin))){
            perror("Error al redirigir la entrada estandar");
            return EXIT_FAILURE;
        }

        if(dup2(fdo, fileno(stdout))){//da problemas aun como superusuario
            perror("Error al redirigir la salida  estandar");
            return EXIT_FAILURE;
        }

        if(dup2(fde, fileno(stderr))){
            perror("Error al redirigir la salida de error estandar");
            return EXIT_FAILURE;
        }

        //sleep(5);//Dormir hijo (demonio) para que padre acabe antes

        if(execvp(argv[1], &argv[1]) == -1){
            perror("Error al ejecutar el comando");
            return EXIT_FAILURE;
        }
    } else if(pid > 0{
        sleep(10);//Dormir padre para que hijo acabe antes
        printf("Soy el proceso padre!\n");
    }else{
        perror("Error al hacer el fork");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
