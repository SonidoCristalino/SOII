#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>  //tiene la función de exit para salir con el error


//Int es para poder enviarle un entero al sistema operativo
int main(void){

    pid_t PID;  //es como un tipo int PID, 
    int i = 20;

    /*
     * resultado de fork() en PID y si ese es igual a uno, si eso 
     * significa que se produjo un error. Esto es posible porque en minix no
     * puede tener más de 100 procesos ejecutandose. 
     */
    if( (PID = fork() ) == -1 ){

        printf("Error creando al hijo\n");
        exit(1);

    }
    if( PID == 0 ){ //proceso hijo

        printf("Soy el hijo. El PID de mi padre: %i\n", getppid());
        sleep(10);
        printf("Soy el hijo muriendo\n");

    }else{

        printf("Soy el padre. PID del Hijo: %i. El PID de mi padre: %i\n", PID,
                getppid());
        sleep(15);
        printf("Soy el padre muriendo\n");

    }

    return 0;

}
