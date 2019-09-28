#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (void){

    int fd[2], nbytes; //file descriptor
    pid_t pid;      //utilizado para poder atajar el proceso hijo
    // [][][][][][][\n] --> para que sepa dónde parar a imprimir
    char cadena[] = "hola mundo\n"; //cadena que se va a pasar al hijo
    char buffer[80];        //para donde poder almacenar la cadena

    pipe(fd);       //crea el tubo

    //Si hubo un error al crear el hijo
    if( ( pid = fork() ) == -1 ){

        printf("Error creando hijo\n");
        exit(1);

    }

    /*
     * En un momento aparece la palabra fork() comienzan a existir dos procesos donde uno se denomina padre y el otro
     * hijo. Se tiene asignado un espacio de memoria único antes de fork(). Se declara una variable pid, cuando ocurre
     * la función fork() el espacio de memoria se copia igual para el hijo. Ambos códigos son iguales, el padre y el
     * hijo lo mismo que las variables; la única diferencia es son el pid del hijo que será 0, y el padre un número
     * mayor que cero. Como el código es el mismo, entonces el hijo entra cuando se consulta por cero y el del padre
     * cuando se sale por el else. 
     */
    if( pid == 0 ){

        printf("Soy el hijo\n");
        close(fd[0]); // en este caso escribe el hijo
        write(fd[1], cadena, strlen(cadena)+1); //lo que dice strlen da el largo de la cadena +1 es para el \0
        sleep(1);

    }else{
        
        printf("Soy el padre\n");
        close(fd[1]); // en este caso el que escucha es el padre
        //sizeof() es para que sepa hasta cuándo va a guardar, que será en este caso 80 porque así es el tamaño del
        //buffer declarado
        nbytes = read(fd[0], buffer, sizeof(buffer)); 
        printf("La cadena recibida fue: %s", buffer);
        printf("Se recibieron: %d\n", nbytes);

        /*
         * NOTA: lo que puede ir en el examen es hacer algo con el buffer. Por ejemplo: 
         * De caracteres a valor decimal, es restarle 48. "1" - 48 = 1 (en decimal). 
         * char cadena[6] = "135.23"
         *
         *
         *
         *
         *
         *
         */
    }

    return 0;
}
