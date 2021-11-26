//Ejercicio11-Pr2.3 - PabloMartinez

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/resource.h>
#include <signal.h>

int main(int argc, char* argv[]) {
    sigset_t blk_set, pending_set;
    char * strseconds;
    int seconds;

    strseconds = getenv("SLEEP_SECS");
    
    if (strseconds == NULL) {
        perror("Error obtener los SLEEP_SECS");
        return EXIT_FAILURE;
    }
    
    seconds = atoi(strseconds);

    printf("Durmiendo %ds\n", seconds);

    sigemptyset(&blk_set);
    sigaddset(&blk_set, SIGINT);
    sigaddset(&blk_set, SIGTSTP);

    if(sigprocmask(SIG_BLOCK, &blk_set, NULL) == -1){
        perror("Error al bloquear");
        return EXIT_FAILURE;
    }

    sleep(seconds);
    //sleep(5);

    if(sigpending(&pending_set)){
        perror("Error al devolver las señales pendientes");
        return EXIT_FAILURE;
    }

    if (sigismember(&pending_set, SIGINT)) {
        printf("Señal SIGINT recibida\n");
    } else if (sigismember(&pending_set, SIGTSTP)) {
       printf("Señal SIGTSTP recibida\n");
    }

    if(sigprocmask(SIG_UNBLOCK, &blk_set, NULL) == -1){
        perror("Error al desbloquear");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
