#include <iostream>
#include <iomanip>
#include <fstream>
#include"priority_queue.h"

struct paciente {
    std::string nombre;
    int propridad;
    int espera;
};

bool operator<(paciente const&a, paciente const&b){

    return a.propridad > b.propridad || (a.propridad==b.propridad && a.espera>b.espera);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int eventos;
    std::cin >> eventos;
    if (eventos == 0)
        return false;

    PriorityQueue<paciente,std::less<paciente>> cola;

    char opcion;
    std::string nombre;
    int prioridad;

    while (eventos--) {
        std::cin >> opcion;
        if (opcion == 'I') {
            std::cin >> nombre >> prioridad;
            cola.push({ nombre,prioridad,eventos });
        }
        else {
            auto aux = cola.top();
            cola.pop();
            std::cout << aux.nombre<<"\n";
        }

    }
    std::cout << "---\n";

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
