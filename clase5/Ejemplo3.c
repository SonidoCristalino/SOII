#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (void){

    /*
     * Se invierten las minúsculas y mayusculas: 
     * se sabe que la A mayúscula es 65, la a minúscula: 97, y la z mayúscula 122. 
     * Lo que se obtiene es: 
     *          [65] ---> [A]
     *          [66] ---> [B]
     *          [67] ---> [C]
     *          ...
     *          [97] ---> [a]
     *          [98] ---> [b]
     *          [100] ---> [c]
     *          ...
     *          [122] ---> [z]
     */

    int fd[2], nbytes; //file descriptor
    pid_t pid;      //utilizado para poder atajar el proceso hijo
    char cadena[] = "HoLa mUnDo\n"; //cadena que se va a pasar al hijo
    char buffer[80];        //para donde poder almacenar la cadena

    pipe(fd);       //crea el tubo

    //Si hubo un error al crear el hijo
    if( ( pid = fork() ) == -1 ){

        printf("Error creando hijo\n");
        exit(1);

    }

    if( pid == 0 ){

        printf("Soy el hijo\n");
        close(fd[0]); // en este caso escribe el hijo ¡¡¡OJO CON ESTO!!!!
        write(fd[1], cadena, strlen(cadena)+1); //lo que dice strlen da el largo de la cadena +1 es para el \0
        sleep(1);

    }else{
        
        printf("Soy el padre\n");
        close(fd[1]); // en este caso el que escucha es el padre
        nbytes = read(fd[0], buffer, sizeof(buffer)); 
        printf("La cadena recibida fue: %s", buffer);
        printf("Se recibieron: %d\n", nbytes);

        int i = 0; 

        //Pasamos a mayusculas
        while( cadena[i] != '\n' ){

            if( (cadena[i] >= 97) && (cadena[i] <= 122) ){
                cadena[i] = cadena[i] - 32;
            }
            i++;

        }

        printf("La cadena convertida es: %s", cadena);

    }

    return 0;
}
