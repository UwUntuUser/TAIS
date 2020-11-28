// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include"Digrafo.h"




// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    Digrafo g(std::cin);

    if (!std::cin)
        return false;

    Digrafo g_inv = g.inverso();
    bool exists = false;

    for (int v = 0; v < g.V(); v++) {
        if (g.ady(v).size() == 0 && g_inv.ady(v).size() == g.V() - 1) { 
            // si un vertice en el grafo g tiene grado de salida 0 y grado de salida V-1 en el inverso entonces es sumidero
            std::cout << "SI " << v << "\n";
            exists = true;
        }
    }

    if (!exists) {
        std::cout << "NO\n";
    }
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