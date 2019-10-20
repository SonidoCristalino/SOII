#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(void){

    pid_t PID;
    char cadena[] = "Hola mundo\n";
    char buffer[90];            //donde se almacena la cadena
    int nbytes = 0;
    int fd[2];

    pipe(fd);                   //creamos la tubería

    if( (PID = fork()) == 1 ){

        printf("Error al crear proceso hijo\n");
        exit(1);

    }

    if( PID == 0 ){             //proceso hijo. NO utilizamos getpid()

        close(fd[0]);           //Se escribe por la tubería 1
        write(fd[1], cadena, strlen(cadena) + 1);
        sleep(1);               //se asegura de que luego de escribir, le de tiempo

    }else{                      //proceso padre

        close(fd[1]);
        nbytes = read(fd[0], buffer, sizeof(buffer));
        printf("La cadena recibida fue: %s", buffer);

    }

    return 0;
}
