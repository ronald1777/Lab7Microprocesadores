/*---------------------------------------------------------------------------
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERIA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACION
* RONALD CATÚN
------------------------------------------------------------------------------*/
#include <iostream>
#include <sys/wait.h>   // CORRECCIÓN: faltaba este header para usar wait()
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>

int main() 
{ 
    fork();
    fork();
    printf("Hello World! I am process %d and my parent is %d.\n",
           getpid(), getppid());

    // CORRECCIÓN: se agrega wait() para que los procesos padre esperen
    // a sus hijos antes de terminar, evitando procesos zombi.
    // wait() retorna -1 cuando no quedan mas hijos, por lo que el bucle
    // termina naturalmente sin necesidad de contar cuantos hijos hay.
    while (wait(nullptr) > 0);

    return EXIT_SUCCESS;
} 
