#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>  //tiene la función de exit para salir con el error
#include<string.h>  //se utiliza strlen, devuelve el largo de la cadena

//Devuelve un entero  para poder enviarle un entero al sistema operativo
int main(void){

    pid_t PID;
    int fd[2];  //se crea un vector con dos posiciones. Por acá se envia msj

    int nbytes;
    char cadena[] = "Hola mundo\n";
    char buffer[80];
    pipe(fd);

    if( (PID = fork() ) == -1 ){        //en caso de error

        printf("Error creando al hijo\n");
        exit(1);

    }
    if( PID == 0 ){ //proceso hijo

        close(fd[0]);
        printf("Soy el hijo. El hijo enviando\n");
        write(fd[1], cadena, strlen(cadena)+1);

    }else{          //Proceso padre

        close(fd[1]);
        nbytes = read(fd[0], buffer, sizeof(buffer));
        printf("El padre recibiendo\n");
        printf("%d caracteres\n", nbytes);  //Se imprime la cantidad de bytes
        printf("Mensaje: %s\n", buffer);    //Se muestra lo que hay dentro del buffer

    }

    return 0;

}
