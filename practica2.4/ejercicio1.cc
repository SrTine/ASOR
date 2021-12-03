//Ejercicio1-Pr2.4 - PabloMartinez

#include <unistd.h>//para el pipe
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    int pipefd[2];//estructura para guardar dos descriptores de fichero que hacen referencia a los extremos del canal
    /*  pipe[0] referencia al extremo de lectura de la tuberia
        pipefd[1] referencia al extremo de escritura de la tuberia
    */
    pid_t pid;

    if (argc != 5) {
        printf("Debe introducir dos comandos con la estructura...\n");
        printf("%s comando1 argumento1 comando2 argumento2\n", argv[0]);
        return EXIT_FAILURE;
    }

    if(pipe(pipefd) == -1){//crea un canal unidericional que puede ser usado para comunicacion entre procesos
        perror("Error al crear la tuberia");
        return EXIT_FAILURE;
    }

    pid = fork();
    if(pid == -1){
        perror("Error al hacer el fork");
        return EXIT_FAILURE;

    }else if (pid > 0) {//proceso padre
        if(close(pipefd[0]) == -1){
            perror("Error cerrar descriptor de fichero lectura padre");
            return EXIT_FAILURE;
        }
        if(dup2(pipefd[1], fileno(stdout)) == -1){//redireccionará la salida estándar al extremo de escritura de la tubería
            perror("Error al redireccionar la salida estandar");
            return EXIT_FAILURE;
        }
        if(close(pipefd[1]) == -1){
            perror("Error al cerrar descriptor de fichero escritura padre");
            return EXIT_FAILURE;
        }

        //descriptores no necesarios cerrados
        if(execlp(argv[1], argv[1], argv[2], NULL) == -1){
            perror("Error al ejecutar el comando en padre");
            return EXIT_FAILURE;
        }

    }else if (pid == 0){//proceso hijo
        if(close(pipefd[1]) == -1){
            perror("Error cerrar descriptor de fichero escritura hijo");
            return EXIT_FAILURE;
        }
        if(dup2(pipefd[0], fileno(stdin)) == -1){//redireccionará la entrada estándar al extremo de escritura de la tubería
            perror("Error al redireccionar la entrada estandar");
            return EXIT_FAILURE;
        }
        if(close(pipefd[0]) == -1){
            perror("Error al cerrar descriptor de fichero lectura hijo");
            return EXIT_FAILURE;
        }

        //descriptores no necesarios cerrados
        if(execlp(argv[3], argv[1], argv[4], NULL) == -1){
            perror("Error al ejecutar el comando en hijo");
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}

