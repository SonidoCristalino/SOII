#include <stdio.h> 

//Debería de invertir el vector

int main (void){

    int vec[5] = {5, 4, 3, 2, 1};
    int i, aux;

    for( i = 0; i < 3; i++){

        aux = vec[5-i-1];

        vec[5-i-1] = vec[i];

        vec[i] = aux;

    }

    for(int a = 0; a < 5; a++) {

        printf("[%d] = %d\n", a, vec[a]);

    }
    return 0;   
}

