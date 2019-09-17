#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(void){

    pid_t PID;
    int i = 20;
    int s; //variable compartida que es utilizada como sem�foro

    if( (PID = fork() ) == -1 ){

        printf("Error creando al hijo\n");
        exit(1);

    }
    if( PID == 0 ){ //proceso hijo

        wait(s); //se bloquea para que ning�n proceso m�s pueda ingresar
            printf("Soy el hijo. El PID de mi padre: %i\n", getppid());
            sleep(10);
            printf("Soy el hijo muriendo\n");
        signal(s); //habilita v�a sem�foro el ingreso de otro proceso a la regi�n cr�tica

    }else{

        printf("Soy el padre. PID del Hijo: %i. El PID de mi padre: %i\n", PID, getppid());
    }

    return 0;
}
