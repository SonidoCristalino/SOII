#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (void){

    int fd[2];
    int nbytes;
    pid_t pid;      //utilizado para poder atajar el proceso hijo
    char cadena[] = "135.23"; //numeros almacenados como cadena
    float numero;
    char buffer[80];

    pipe(fd);       //funcion que crea la conexión entre procesos

    //Si hubo un error al crear el hijo
    if( ( pid = fork() ) == -1 ){

        printf("Error creando hijo\n");
        exit(1);

    }
    //El HIJO será el que escribe
    if( pid == 0 ){

        printf("Soy el hijo\n");
        close(fd[0]);
        //strlen() devuelve el largo de la cadena +1 para el \0
        write(fd[1], cadena, strlen(cadena)+1);
        sleep(1);

    }else{

        //Proceso PADRE quien es el que recibe la cadena
        close(fd[1]);
        nbytes = read(fd[0], buffer, sizeof(buffer));
        printf("La cadena recibida fue: %s\n", buffer);
        printf("Se recibieron: %d\n", nbytes);

        for( int i = 0; i < nbytes; i++ ){

            if ( i == 3 ){
                printf("El valor en %d es: %c\n", i, buffer[i]);
            }else{
                buffer[i] = buffer[i] - 48;
                printf("El valor en %d es es: %d\n", i, buffer[i]);
            }
        }

        printf("El valor de nbytes es: %d\n", nbytes);

        //El error esta en que no se puede visualizar con el
        //formato float porque hay un caracter de punto en la posición
        //3
        numero += buffer[0] * 100;
        numero += buffer[1] * 10;
        numero += buffer[2];
        numero += buffer[4] * 0,1;
        numero += buffer[5] * 0,01;

        printf("El numero es %f\n", buffer);

    }

    return 0;
}
