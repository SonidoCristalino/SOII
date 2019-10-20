#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void){

    pid_t PID;
    char cadena[] = "Hola Mundo\n";
    char buffer[90];
    int fd[2];
    int bytes = 0;

    pipe(fd);

    if( (PID = fork()) == -1 ){

        printf("Error al crear el proceso hijo\n");
        exit(1);

    }

    if( PID == 0 ){             //Recibe el hijo

        close(fd[1]);
        bytes = read(fd[0], buffer, sizeof(buffer));
        printf("La cadena que se recibio es: %s", buffer);
        printf("La cantidad de bytes es de: %d\n", bytes);

    }else{                      //Escribe el padre

        close(fd[0]);
        write(fd[1], cadena, strlen(cadena) + 1);

    }

    return 0;
}
