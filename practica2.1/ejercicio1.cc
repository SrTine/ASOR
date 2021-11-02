//Ejercicio1-Pr2.1 - PabloMartinez

//Añadir el código necesario para gestionar correctamente los errores generados por la llamada a setuid(2). Consultar en el manual el propósito de la llamada y su prototipo.

//al ejecutarlo por terminal nos sale el mensaje operacion denegada, eso es porque estamos cambiando el id del proceso en concreto y esta accion necesita permisos.
	//Por defecto, el canal de error stderr muestra el mensaje por pantalla, pero podemos rederigir este mensaje utilizando -$ ./ejercicio1 2> ficheroError.txt
	//De esta manera, ficheroError.txt contendra el error producido por stderror del programa
//Realizando la configuracion como superusuario, no da problemas de ejecuccion

#include <sys/types.h>	//para el setuid
#include <unistd.h>	//para el setuid
#include <stdio.h>	//para el perror
#include <errno.h>	//para perror y errno
#include <string.h>	//para el sterror

int main(){

	if(setuid(2) != 0){//la funcion setuid asocia el id pasado por parametro al proceso
		perror(strerror(errno));//la funcion perror escribe en el canal de error stderror  el string que proporciona la funcion strerror que gestiona con el valor de errno que error se ha producidos (por defecto el canal de error es la pantalla)
	}

	return 1;
}

//Informacion del manual
//The  routine  perror() produces a message on the standard error output, describing the last error encountered during a call to a system or library function.
//The  strerror()  function  returns  a  pointer to a string that describes the error code passed in the argument errnum.

