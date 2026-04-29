/*--------------------------------------------------------------------------- 
* UNIVERSIDAD DEL VALLE DE GUATEMALA
* FACULTAD DE INGENIERIA
* DEPARTAMENTO DE CIENCIA DE LA COMPUTACION
* RONALD CATÚN 
------------------------------------------------------------------------------*/
#include <iostream>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>     

using namespace std;

int main() {
    int a;
    cout << "Please enter the value to be stored in a: ";

    // CORRECCIÓN: Validar que la entrada sea un número entero válido
    // En el original no se validaba; si el usuario ingresaba una letra
    // cin quedaba en estado de error y 'a' tenía valor basura.
    if (!(cin >> a)) {
        cerr << "Error: ingresa un numero entero valido." << endl;
        return EXIT_FAILURE;
    }
    cout << "\n";

    pid_t res;
    res = fork();

    // Si el hijo no se crea correctamente → ERROR
    if (res < 0) {
        perror("fork not created");
        exit(EXIT_FAILURE);
    }
    // Si res > 0 estamos en el PADRE: fork() retorna el PID del hijo
    else if (res > 0) {
        cout << "Printed from Parent Num. Process: " << getpid() << endl;
        a = a + 5;
        cout << "a printed from Parent: " << a << "\n" << endl;

        // CORRECCIÓN: se agrega wait() para que el padre espere al hijo
        // antes de terminar. Sin esto, el hijo puede quedar como zombi
        // si el padre termina primero y no recoge el estado de salida.
        wait(nullptr);
    }
    // Si res == 0 estamos en el HIJO: el OS asigna ID local 0 al hijo
    else {
        cout << "Printed from Child Num. Process: " << getpid() << endl;
        a = a + 10;
        cout << "a printed from Child: " << a << "\n" << endl;

        // El hijo termina con exit() para liberar recursos correctamente
        exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}
