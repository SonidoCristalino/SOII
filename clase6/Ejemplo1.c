#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (void){

    int i = 20;
    int fd[2], nbytes; 
    pid_t pid;      
    char cadena[] = "01000001+01100001";
    char buffer[80];        

    pipe(fd);       //crea el tubo

    if( ( pid = fork() ) == -1 ){

        printf("Error creando hijo\n");
        exit(1);

    }

    if( pid > 0 ){ // proceso padre

        close(fd[0]); 
        write(fd[1], cadena, strlen(cadena)+1); 

    }else{  //Proceso hijo
        
        /*
         * Valor en ASCII el 0 = 48 y el 1 = 49
         */

        close(fd[1]); 
        nbytes = read(fd[0], buffer, sizeof(buffer)); 
        int vector[8] = {128, 64, 32, 16, 8, 4, 2, 1};
        char c1 = 0;
        char c2 = 0;

        //para el primer tramo
        for( int j = 0; j < 8; j++ ){
            c1 = c1 + ((buffer[j] - 48) * vector[j]);
        }
        
        //para el segundo tramo (luego del '+')
        for( int j = 9; j < 17; j++ ){
            c2 = c2 + ((buffer[j] - 48) * vector[j]);
        }

        /*
         * El resultado es C1 = 65 y c2 = 97. 
         * Cuando se imprimen las variables vía char, lo que sale por pantalla son los caracteres ASCII. Cuando se
         * imprime la suma, salen en formato enteros. 
         */
        printf("C1: %c, C2 = %c\n", c1, c2); //c1 = A, c2 = a
        printf("Suma = %d\n", c1 + c2); //Suma = 162

    }

    return 0;
}
