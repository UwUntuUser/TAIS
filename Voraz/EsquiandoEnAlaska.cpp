
// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <cstdlib>
// función que resuelve el problema


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num_groups;
    std::cin >> num_groups;
    if (num_groups == 0)
        return false;

    std::priority_queue<int> groups;
    std::priority_queue<int> skis;
    int aux;

    for (int i = 0; i < num_groups; i++) {
        std::cin >> aux;
        groups.push(aux);
    }
    for (int i = 0; i < num_groups; i++) {
        std::cin >> aux;
        skis.push(aux);
    }
    int sol = 0;
    while (!groups.empty()) {
        sol += std::abs(groups.top() - skis.top());
        groups.pop();
        skis.pop();
    }
    std::cout << sol << "\n";
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
