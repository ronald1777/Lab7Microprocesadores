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
    int n;
    cout << "Ingresa la cantidad de procesos hijo a crear: ";

    // CORRECCIÓN: Validar que la entrada sea un entero positivo valido.
    // El original no validaba; una entrada no numerica dejaba n con basura.
    if (!(cin >> n) || n <= 0) {
        cerr << "Error: ingresa un numero entero positivo." << endl;
        return EXIT_FAILURE;
    }

    for (int i = 0; i < n; i++) {
        pid_t pid = fork();

        if (pid < 0) {
            perror("fork not created");
            exit(EXIT_FAILURE);

        } else if (pid == 0) {

            cout << "Child Process: " << i + 1
                 << ", PID: "  << getpid()
                 << ", PPID: " << getppid() << endl;
            exit(EXIT_SUCCESS);
        }
    // CORRECCIÓN: se elimino el sleep(5) que existia en el original.
    // sleep() solo retrasaba innecesariamente la recoleccion de hijos;
    // wait() ya bloquea al padre el tiempo necesario por si solo.
    for (int i = 0; i < n; i++) {
        wait(nullptr);
    }

    cout << "Todos los procesos hijo han finalizado." << endl;
    return EXIT_SUCCESS;
}
