//Ejercicio9-Pr2.2 - PabloMartinez --hecho
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>//para la fun stat
#include <sys/stat.h>//para la fun stat
#include <unistd.h>//para la fun stat
#include <errno.h>
#include <string.h>
#include <fcntl.h>//para las macros de los tipos
#include <time.h>

//macros para el st_mode del fichero
char* tipo(long unsigned type) {
    if (S_ISSOCK(type)) return "socket";
    else if (S_ISLNK(type)) return "symbolic link";
    else if (S_ISREG(type)) return "regular file";
    else if (S_ISBLK(type)) return "block device";
    else if (S_ISDIR(type)) return "directory";
    else if (S_ISCHR(type)) return "character device";
    else if (S_ISFIFO(type)) return "FIFO";
    else return "Error en el tipo de fichero";
}

int main(int argc, char ** argv) {
    char* fname;
    struct stat st;//estructura para guardar la informacion del fichero

    if (argc > 1){
        fname = argv[1];
    }
    else{
        perror("Debe introducir por argumento un fichero");
        return EXIT_FAILURE;
    }

    if(stat(fname, &st) == -1){//devuelve 0 en caso de exito y -1 en caso de error
        perror("Error al guardar info en estructura stat");
        return EXIT_FAILURE;
    }

    printf("Device: %d:%02d\n", major(st.st_dev), minor(st.st_dev));
    printf(" Inode: %lu\n", st.st_ino);
    printf("  Type: %s\n", tipo(st.st_mode));
    printf("Access: %s\n", ctime(&st.st_atime));

    //¿Que diferencia hay entre st_mtime y st_ctime?

    //st_mtime -> ultima vez que cambiaron los datos
    //st_ctime -> ultima vez que cambio el inodo

    return 0;
}
