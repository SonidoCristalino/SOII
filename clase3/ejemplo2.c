#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>  //tiene la función de exit para salir con el error
#include<string.h>  //se utiliza strlen, devuelve el largo de la cadena

//Devuelve un entero  para poder enviarle un entero al sistema operativo
int main(void){

    pid_t PID;  //es como un tipo int PID, 
    int fd[2];  //se crea un vector con dos posiciones. Por acá se envia msj
    
    //el que recibe cuenta la cantidad de bytes que pasaron por el pipe
    int nbytes; 
    char cadena[] = "Hola mundo\n"; //[h|o|...|\n] Es para el que envia
    //Para el que recibe para hospedar el mensaje, no sabe cuanto va a 
    char buffer[80]; 

    /*
     * Se genera el pipe acá para que los dos proceso lo hereden. 
     */
    pipe(fd);   
    if( (PID = fork() ) == -1 ){        //errror

        printf("Error creando al hijo\n");
        exit(1);

    }
    if( PID == 0 ){ //proceso hijo

        /*
         * para poder escribir primero se requiere cerrar el vector. 
         * Con el write se indica que se escribe en fd1, ¿qué cosa? la cadena,
         * ¿qué largo? El largo de la cadena + 1 para poder escribir el \0
         */
        close(fd[0]);   //esto está realizado así, y hay que hacerlo así. 
        printf("Soy el hijo. El hijo enviando\n");
        write(fd[1], cadena, strlen(cadena)+1);

    }else{          //Proceso padre

        /*
         * El padre hace al reves, cierra el 1. 
         * Lee el mensaje que se envía desde el otro lado, y lo hospeda en
         * buffer. sizeof() devuelve la cantidad de bytes de lo que se le ponga. 
         */
        close(fd[1]);
        /*
         * Lo que hace read es devolver la cantidad de bytes que recibe desde el
         * pipe/tubo
         */
        nbytes = read(fd[0], buffer, sizeof(buffer));
        printf("El padre recibiendo\n");
        printf("%d caracteres\n", nbytes);  //Se imprime la cantidad de bytes
        /*
         * cuando se le indica %s espera que la cadena termine con \0
         */
        printf("Mensaje: %s\n", buffer);    

    }

    return 0;

}
