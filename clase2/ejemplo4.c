#include <stdio.h> 

//Con la inversión se genera una función. 

/*
 * Se le pasa la dirección al primer elemento del vector. Se le pasa el puntero 
 * para que sea más 
 */
void imprimir(int *p, int n);  

int main (void){

    int vec[5] = {5, 4, 3, 2, 1};
    int i, aux;

    for( i = 0; i < 3; i++){

        aux = vec[5-i-1];

        vec[5-i-1] = vec[i];

        vec[i] = aux;
    }

    /*
     * Con el & se pasa la primer posición de memoria del vector
     */
    imprimir(&vec[0], 5);

    return 0;   
}

void imprimir(int *p, int n){

    int i;

    for(i = 0; i < n; i++) {

        /*
         * Con el asterisco se accede al contenido del puntero 
         */
        printf("[%d] = %d\n", i, *p);
        p++;

    }

}
