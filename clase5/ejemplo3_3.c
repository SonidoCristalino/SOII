#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (void){

    int fd[2];
    int nbytes;
    pid_t pid;
    //Cadena con may�sculas y min�sculas
    char cadena[] = "HoLa mUnDo\n";
    char buffer[80];

    pipe(fd);       //Funci�n necesaria para crear la conexi�n

    //Si hubo un error al crear el hijo
    if( ( pid = fork() ) == -1 ){

        printf("Error creando hijo\n");
        exit(1);

    }

    if( pid == 0 ){

        //El hijo ser� quien envie el mensaje
        printf("Soy el hijo\n");
        close(fd[0]);
        write(fd[1], cadena, strlen(cadena)+1);
        sleep(1);

    }else{

        //Ser� el proceso padre quien reciba el mensaje
        printf("Soy el padre\n");
        close(fd[1]);
        nbytes = read(fd[0], buffer, sizeof(buffer));
        printf("La cadena recibida fue: %s", buffer);
        printf("Se recibieron: %d\n", nbytes);

        int i = 0;

        //Pasamos a may�scula
        while( cadena[i] != '\n' ){

            //Se pregunta si la letra se encuentra entre las may�sculas.
            //Caso efectivo se le resta 32 para poder pasarlas a min�scula.
            if( (cadena[i] >= 97) && (cadena[i] <= 122) ){
                cadena[i] = cadena[i] - 32;
            }
            i++;

        }

        printf("La cadena convertida es: %s", cadena);

    }

    return 0;
}
