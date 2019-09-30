#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (void){

    //File Descriptor necesario para generar la conexión entre procesos
    int fd[2];
    //Variable donde se almacenaran la cantidad de caracteres leidos
    int nbytes;
    //Process ID para saber cuándo ejecuta el hijo y cuándo el padre
    pid_t pid;     //utilizado para poder atajar el proceso hijo
    //Cadena que se pasará al proceso que quiera leer
    char cadena[] = "hola mundo\n";
    //Buffer donde se almacenará la cadena leída
    char buffer[80];

    //Necesario para poder generar el pipe por donde se comunicarán los procesos
    pipe(fd);

    //Se evalúa si existe un error al generar el proceso hijo.
    if( ( pid = fork() ) == -1 ){

        printf("Error creando hijo\n");
        exit(1);

    }

    //Proceso hijo el cual va a escribir la cadena
    if( pid == 0 ){

        printf("Soy el hijo\n");
        close(fd[0]); //Se debe cerrar el fd por el que NO se transmitirá nada
        //strlen es una función que permite obtener el largo de la cadena que se le pasa.
        write(fd[1], cadena, strlen(cadena)+1);
        sleep(1);

    }else{

        //Proceso padre, el cual va a recibir la cadena que le pasa el hijo
        printf("Soy el padre\n");
        close(fd[1]); //Se debe cerrar el fd por el que NO se leerá nada
        //sizeof() permite saber el tamaño en bytes de lo que se le pasa, en este caso devolverá 80
        //read() devuelve la cantidad de bytes leídos, por lo que se almacena en nbytes
        nbytes = read(fd[0], buffer, sizeof(buffer));
        printf("La cadena recibida fue: %s", buffer);
        printf("Se recibieron: %d\n", nbytes);
    }

    return 0;
}
