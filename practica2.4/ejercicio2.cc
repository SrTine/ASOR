//Ejercicio2-Pr2.4 - PabloMartinez

#include <unistd.h>//para el pipe
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {
    pid_t pid;
    int p_h[2];
    int h_p[2];

    size_t size;
    char msg;
    char buf[1024];
    char * line;
    int numMensajes = 0;

    if(pipe(h_p) == -1){//crea un canal unidericional que puede ser usado para comunicacion entre procesos
        perror("Error al crear la tuberia");
        return EXIT_FAILURE;
    }

    if(pipe(p_h) == -1){//crea un canal unidericional que puede ser usado para comunicacion entre procesos
        perror("Error al crear la tuberia");
        return EXIT_FAILURE;
    }

    pid = fork();
    if(pid == -1){
        perror("Error al hacer el fork");
        return EXIT_FAILURE;

    }else if (pid > 0){//padre
        //cerramos fd innecesarios
        if(close(p_h[0]) == -1){
            perror("Error cerrar descriptor de fichero lectura padre");
            return EXIT_FAILURE;
        }

        if(close(h_p[1]) == -1){
            perror("Error al cerrar descriptor de fichero escritura hijo");
            return EXIT_FAILURE;
        }

        // El padre lee de la salida estandar y se lo manda al hijo
        // (Entiendo que significa que no podemos redir entrada a pipe)
        do {
            if(getline(&line, &size, stdin) == -1){
                perror("Error al leer");
                return EXIT_FAILURE;
            }

            int bytesWrite = write(p_h[1], line, size);
            if(bytesWrite == -1){
                perror("Error al escibir");
                return EXIT_FAILURE;
            }else if(bytesWrite != size){
                perror("Error no se ha escrito nada");
                return EXIT_FAILURE;
            }

            free(line);
            line = NULL;
            size = 0;

            //ssize_t read(int fd, void *buf, size_t count);
            int bytesRead = read(h_p[0], &msg, 1);
            if(bytesRead == -1){
                perror("Error al leer en el padre");
                return EXIT_FAILURE;
            }else if(bytesRead == 0){
                perror("Error fin de fichero o no se ha leido nada en el padre");
                return EXIT_FAILURE;
            }
            fprintf(stderr, "Recibido mensaje: %c\n", msg);
        } while (msg != 'q');

        if(close(p_h[1]) == -1){
            perror("Error cerrar descriptor de fichero escritura padre");
            return EXIT_FAILURE;
        }

        if(close(h_p[0]) == -1){
            perror("Error al cerrar descriptor de fichero lectura hijo");
            return EXIT_FAILURE;
        }
    }else if(pid == 0){//hijo
        //cerramos fd innecesarios
        if(close(p_h[1]) == -1){
            perror("Error cerrar descriptor de fichero escritura padre");
            return EXIT_FAILURE;
        }

        if(close(h_p[0]) == -1){
            perror("Error al cerrar descriptor de fichero lectura hijo");
            return EXIT_FAILURE;
        }

        do {
            size = read(p_h[0], &buf, 1024);
            if(size == -1){
                perror("Error al leer en el hijo");
                return EXIT_FAILURE;
            }

            if(fputs(buf, stdout) == EOF){
                perror("Error al escribir en la salida estandar");
                return EXIT_FAILURE;
            }

            sleep(1);

            if(numMensajes == 0){
                if(write(h_p[1], "l", 1) == -1){//Escribir listo a padre
                    perror("Error al escribir en el hijo");
                    return EXIT_FAILURE;
                }
            }
            else{
                if(write(h_p[1], "q", 1) == -1){//Escribir fin a padre
                    perror("Error al escribir en el hijo");
                    return EXIT_FAILURE;
                }
            }
            numMensajes++;
        } while (numMensajes < 10);

    }

    printf("Fin programa\n");
    return EXIT_SUCCESS;
}

