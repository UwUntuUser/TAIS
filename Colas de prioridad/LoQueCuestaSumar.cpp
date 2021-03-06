#include <iostream>
#include <iomanip>
#include <fstream>
#include"priority_queue.h"
#include<vector>


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int numeros;
    std::cin >> numeros;
    if (numeros == 0)
        return false;
    
    PriorityQueue<long int> cola;

    int aux;
    while (numeros--) {
        std::cin >> aux;
        cola.push(aux);
    }
    long int esfuerzo = 0;
    long int prim, sec;

    while (cola.size() > 1) // mientras queden mas de dos elementos para sumar
    {
        prim = cola.top();
        cola.pop();

        sec = cola.top();
        cola.pop();

        prim += sec;

        cola.push(prim);
        esfuerzo += prim;
    }

    std::cout << esfuerzo<<"\n";
    // escribir sol

    return true;

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso())
        ;


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}
