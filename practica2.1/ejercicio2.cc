//Ejercicio2-Pr2.1 - PabloMartinez
//Imprimir el código de error generado por la llamada del código anterior, tanto en su versión numérica como la cadena asociada.

#include <sys/types.h>	//para el setuid
#include <unistd.h>	//para el setuid
#include <stdio.h>	//para el perror
#include <errno.h>	//para perror y errno
#include <string.h>	//para el sterror

int main(){

	if(setuid(2) != 0){//la funcion setuid asocia el id pasado por parametro al proceso
		printf("El numero de error es %i \n",errno);//muestra por pantalla el valor de error asociado.
		//para comprobar que el valor de error devuelto es el correcto, podemos comprobar en el terminal dicho valor con: $ echo $?
		perror(strerror(errno));//la funcion perror escribe en el canal de error stderror  el string que proporciona la funcion strerror que gestiona con el valor de errno que error se ha producidos (por defecto el canal de error es la pantalla)
	}

	return 1;
}