/**
 *----------------------------------------
 * primesFork.cpp (corregido)
 * ---------------------------------------
 * UNIVERSIDAD DEL VALLE DE GUATEMALA
 * CC3086 - Programacion de microprocesadores
 * Laboratorio 07 - Ejercicio 5
 * RONALD MANUEL CATÚN CHACÓN
 * ----------------------------------------
 */

#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <cstdlib>
#include <cmath>

using namespace std;

bool isPrime(int number) {
    // Negativos, 0 y 1 no son primos
    if (number <= 1) return false;

    // 2 es el unico primo par
    if (number == 2) return true;

    // Cualquier par mayor que 2 no es primo
    if (number % 2 == 0) return false;

    // Solo revisar divisores impares hasta sqrt(number)
    for (int d = 3; d * d <= number; d += 2) {
        if (number % d == 0) return false;
    }
    return true;
}

void primeTest(long thisNumber, long thisLimit) {
    int posicion = 1;
    while (thisNumber < thisLimit) {
        thisNumber++;
        if (isPrime((int)thisNumber)) {
            if (posicion < 10) {
                cout << thisNumber << " ";
                ++posicion;
            } else {
                cout << thisNumber << endl;
                posicion = 1;
            }
        }
    }
    cout << endl;
}

/*
 * main
 * ----
 * CORRECCIÓN 1: Lee el exponente directamente como int en lugar de
 * leerlo como char y restar 48. Esto permite exponentes de mas de
 * un digito y evita errores con entradas no numericas.
 *
 * CORRECCIÓN 2: Valida que el exponente este en el rango [1, 9]
 * para evitar desbordamientos con pow(10, n) en un long.
 *
 * CORRECCIÓN 3: Agrega wait() en el padre y exit() en el hijo.
 */
int main() {
    int exponente;

    cout << "Ingrese el exponente x para calcular el limite superior 10^x." << endl;
    cout << "Ejemplo: si ingresa 3, se buscaran primos entre 0 y 1000 (10^3)." << endl;
    cout << "x = ";

    // CORRECCIÓN: leer directamente como int, no como char
    if (!(cin >> exponente) || exponente < 1 || exponente > 9) {
        cerr << "Error: ingresa un entero entre 1 y 9." << endl;
        return EXIT_FAILURE;
    }

    long limit = (long)pow(10, exponente);
    cout << endl;
    cout << "Se buscaran numeros primos en el rango [0, " << limit << "]." << endl;
    cout << "Iniciando calculo..." << endl;
    cout << endl;
    cout << "Los siguientes valores son numeros primos:" << endl;

    long i = 0;
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return EXIT_FAILURE;
    }

    if (pid == 0) {
        cout << "\nNumeros primos calculados por el hijo (PID: "
             << getpid() << "): " << endl;
        primeTest(i, limit / 2);

        // CORRECCIÓN: el hijo debe llamar a exit() para liberar sus
        // recursos y no continuar ejecutando codigo del padre.
        exit(EXIT_SUCCESS);
    } else {
        cout << "\nNumeros primos calculados por el padre (PID: "
             << getpid() << "): " << endl;
        primeTest((limit / 2) + 1, limit);

        // CORRECCIÓN: wait() evita que el hijo quede como proceso zombi.
        // Sin wait(), el padre puede terminar antes que el hijo, dejando
        // la salida de ambos mezclada en la terminal, y el hijo queda
        // como zombi hasta que init/systemd lo recoge.
        wait(nullptr);
    }

    return EXIT_SUCCESS;
}
