//Ejercicio17-Pr2.2 - PabloMartinez -- hecho
#include <stdio.h>
#include <unistd.h>//para la funcion readlink
#include <fcntl.h>
#include <stdlib.h>
#include <sys/types.h>//para la funcion fdopendir
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>//para la funcion fdopendir

int main(int argc, char ** argv) {
    char* path;
    int fd;
    DIR* dir;
    off_t sum_size = 0;//para calcular el tamanio
    char currstr[FILENAME_MAX];
    char linkpath[FILENAME_MAX];
    struct dirent* dt;
    struct stat st;

    if (argc > 1){
        path = argv[1];
    }
    else{
        perror("Debe introducir por argumento la ruta de un directorio");
        return EXIT_FAILURE;
    }

    fd = open(path, O_RDONLY | O_DIRECTORY);

    if(fd == -1){
        perror("Error al abrir el directorio");
        return EXIT_FAILURE;
    }

    dir = fdopendir(fd);//recibe el identificador del directorio

    if(dir == NULL){
        perror("Error al abrir el directorio");
        return EXIT_FAILURE;
    }

    dt = readdir(dir);

    while (dt != NULL) {//mientras que hayan entradas en el directorio
        if (dt->d_name[0] != '.') {

            strncpy(currstr, path, FILENAME_MAX);
            strncat(currstr, "/", FILENAME_MAX-1);
            strncat(currstr, dt->d_name, FILENAME_MAX);

            if(lstat(currstr, &st) == -1){
                perror("Error al guardar info en estructura stat");
                return EXIT_FAILURE;
            }

            switch (st.st_mode & S_IFMT) {
                case S_IFDIR://si es un directorio
                    strncat(currstr, "/", FILENAME_MAX-1); 
                    break;
                case S_IFLNK://si es un enlace simbolico
                    readlink(currstr, linkpath, FILENAME_MAX);
                    strncat(currstr, " -> ", FILENAME_MAX-4);
                    strncat(currstr, linkpath, FILENAME_MAX);
                    break;
                case S_IFREG://si es un fichero regular
                    sum_size += st.st_size;
                    break;
                default: strncat(currstr, "?", FILENAME_MAX-1); break;
            }

            printf("%s\n", currstr);
        }

        dt = readdir(dir);//leemos la siguiente entrada
    }

    printf("Tamanio total: %ldkb\n", sum_size / 1024);

    return 0;
}
