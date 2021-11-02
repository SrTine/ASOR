//Ejercicio3-Pr2.1 - PabloMartinez
//Escribir un programa que imprima todos los mensajes de error disponibles en el sistema. Considerar inicialmente que el límite de errores posibles es 255.

#include <sys/types.h>	//para el setuid
#include <unistd.h>	//para el setuid
#include <stdio.h>	//para el perror
#include <errno.h>	//para perror y errno
#include <string.h>	//para el sterror

int main() {
	for(int i = 0; i < 255; i++){
		perror(strerror(i));//imprimimos por el canal de error por defecto (por pantalla) el string que devuelve strerror del error asociado al valor entero i.
	}

	return 0;
}
