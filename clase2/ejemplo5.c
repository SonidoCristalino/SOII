/*
 * Se quiere programar de forma concurrente. 
 *
 */
#include <stdio.h>
#include <unistd.h>  //necesario para el fork y pid_t
#include <stdlib.h>

int main(void){ //este es el proceso padre

    //declaración de tipo de dato pid_t para alojar PID propio de linux
    pid_t PID;  

    /*
     * Se le asigna el resultado de la funcion Fork. Lo que hace el if es hacer
     * ejecutar el fork, devuelve algo y eso se lo asigna a PID. Luego lo
     * compara con -1 (por si es un error). Es la forma tradicional hacer la
     * asignación dentro del if. 
     * Si le da -1 es porque dio error. minix tiene una tabla de 99 procesos
     * posible, en realidad es 100 0-99. Cuando se crean más de 100 procesos
     * hijos entonces sale con -1, es uno de los casos por los que puede fallar,
     * es una pregunta d eexamen. Está llena la tabla de procesos de minix
     */
    if( (PID = fork() == -1 ) ){
        printf("Error creando el hijo\n");
        exit(1);
    }
    /*
     * Aca se escribe el comportamiento del hijo. Se copia la memoria identica,
     * los espacios de memoria, pero no se copia la variable, que en el caso del
     * hijo es cero, y el padre siempre es mayor que 0, por ejemplo 2420
     * Ejemplo practico: Padre = 1200. Cuando se ejecuta fork() se crea un
     * proceso hijo y le asigna un PID 2420. En el caso de hijo le fuerza el PID
     * a 0, y el padre pasa a tener el PID del hijo. 
     *
     * No se puede laburar con la i, porque se va a modificar en el espacio del
     * hijo y no en el padre. Recordar que son dos variables distintas. 
     */
    if( PID == 0 ){

        printf("Soy el Hijo\n");

    }else{

    /*
     * Aca se escribe el comportamiento del ppadre
     */
        printf("Soy el Padre\n");
    }

    return 0;
}
