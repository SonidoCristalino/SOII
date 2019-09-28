#include <stdio.h>

semaforo recurso_1;
semaforo recurso_2;

void proceso_A(void) {

    wait(recurso_1);
    wait(recurso_2);

    /*
     * Se comentan las lineas ya que es mejor implementar las llamadas wait() y signal()
    down(&recurso_1);
    down(&recurso_2);
    */

    usar_ambos_recursos();

    /*
        up(&recurso_2);
        up(&recurso_1);
    */

    signal(&recurso_2);
    signal(&recurso_1);
}

void proceso_B(void) {

    wait(recurso_1);
    wait(recurso_2);

    /*
    down(&recurso_2);
    down(&recurso_1);
    */

    usar_ambos_recursos();

    /*
    up(&recurso_1);
    up(&recurso_2);}
    */

    signal(&recurso_2);
    signal(&recurso_1);
}
