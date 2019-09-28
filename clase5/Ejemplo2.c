#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (void){

    /*
     * Se convierten de cadena a número
     */

    int fd[2], nbytes; //file descriptor
    pid_t pid;      //utilizado para poder atajar el proceso hijo
    char cadena[] = "135.23"; //cadena que se va a pasar al hijo
    float numero;
    char buffer[80];        //para donde poder almacenar la cadena

    pipe(fd);       //crea el tubo

    //Si hubo un error al crear el hijo
    if( ( pid = fork() ) == -1 ){

        printf("Error creando hijo\n");
        exit(1);

    }
    if( pid == 0 ){

        printf("Soy el hijo\n");
        close(fd[0]); // en este caso escribe el hijo
        write(fd[1], cadena, strlen(cadena)+1); //lo que dice strlen da el largo de la cadena +1 es para el \0
        sleep(1);

    }else{
        
        printf("Soy el padre\n");
        close(fd[1]); // en este caso el que escucha es el padre
        nbytes = read(fd[0], buffer, sizeof(buffer)); 
        printf("La cadena recibida fue: %s\n", buffer);
        printf("Se recibieron: %d\n", nbytes);

        /*
        for( int i = 0; i < nbytes; i++ ){

            buffer[i] = buffer[i] - 48;
            printf("El valor es: %d\n", buffer[i]);
        }

        //se divide todo por 10 
        for( int i = 100, x = 0; x < nbytes; i = i/10, x++ ){

            numero = numero + buffer[x] * i;

        }
        printf("El valor es %d\n", numero);
        */

        buffer[0] = buffer[0] - 48; 
        buffer[1] = buffer[1] - 48;
        buffer[2] = buffer[2] - 48;
        buffer[4] = buffer[4] - 48;
        buffer[5] = buffer[5] - 48;

        printf("La cadena es %d\n", buffer);

        numero = numero * buffer[0] * 100;
        numero = numero * buffer[1] * 10;
        numero = numero * buffer[2];
        numero = numero * buffer[4] * 0,1;
        numero = numero * buffer[5] * 0,01;

        printf("El numero es %f\n", buffer);

    }


    return 0;
}
