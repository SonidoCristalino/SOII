#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (void){

    //File Descriptor necesario para generar la conexi�n entre procesos
    int fd[2];
    //Variable donde se almacenaran la cantidad de caracteres leidos
    int nbytes;
    //Process ID para saber cu�ndo ejecuta el hijo y cu�ndo el padre
    pid_t pid;     //utilizado para poder atajar el proceso hijo
    //Cadena que se pasar� al proceso que quiera leer
    char cadena[] = "hola mundo\n";
    //Buffer donde se almacenar� la cadena le�da
    char buffer[80];

    //Necesario para poder generar el pipe por donde se comunicar�n los procesos
    pipe(fd);

    //Se eval�a si existe un error al generar el proceso hijo.
    if( ( pid = fork() ) == -1 ){

        printf("Error creando hijo\n");
        exit(1);

    }

    //Proceso hijo el cual va a escribir la cadena
    if( pid == 0 ){

        printf("Soy el hijo\n");
        close(fd[0]); //Se debe cerrar el fd por el que NO se transmitir� nada
        //strlen es una funci�n que permite obtener el largo de la cadena que se le pasa.
        write(fd[1], cadena, strlen(cadena)+1);
        sleep(1);

    }else{

        //Proceso padre, el cual va a recibir la cadena que le pasa el hijo
        printf("Soy el padre\n");
        close(fd[1]); //Se debe cerrar el fd por el que NO se leer� nada
        //sizeof() permite saber el tama�o en bytes de lo que se le pasa, en este caso devolver� 80
        //read() devuelve la cantidad de bytes le�dos, por lo que se almacena en nbytes
        nbytes = read(fd[0], buffer, sizeof(buffer));
        printf("La cadena recibida fue: %s", buffer);
        printf("Se recibieron: %d\n", nbytes);
    }

    return 0;
}
