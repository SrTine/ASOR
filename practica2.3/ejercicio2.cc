//Ejercicio2-Pr2.3 - PabloMartinez

#include <unistd.h>
#include <stdlib.h>
#include <sched.h>//para la funciones sched
#include <stdio.h>
#include <string.h>

const char* parseToString(int policy) {
    switch (policy) {
        case SCHED_FIFO:
            return "First-in first-out policy";
        case SCHED_RR:
            return "Round-robin policy";
        case SCHED_OTHER:
            return "Other (round-robin policy)";
        default:
            return "Error al obtener la politica de planificacion";
    }
}

int main() {
    int policy, schmin, schmax;
    sched_param schpar;//estructura para guardar sch
    const char* schstr;

    policy = sched_getscheduler(0);
    if(policy == -1){
        perror("Error al obtener la politica de planificacion");
        return EXIT_FAILURE;
    }

    schstr = parseToString(sch);

    if(sched_getparam(0, &schpar) == -1){
        perror("Error al guardar los parametros del proceso");
        return EXIT_FAILURE;
    }

    schmin = sched_get_priority_min(policy);
    schmax = sched_get_priority_max(policy);

    if(schmin == -1 || schmax == -1){
        perror("Error al obtener los valores maximo o minimo de prioridad");
        return EXIT_FAILURE;
    }

    printf("Scheduler: %s\n", schstr);
    printf("Priority:  %d\n", schpar.sched_priority);
    printf("Min priority: %d\n", schmin);
    printf("Max priority: %d\n", schmax);

    return EXIT_SUCCESS;
}