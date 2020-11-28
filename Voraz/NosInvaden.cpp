// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include<queue>

int solve(std::priority_queue<int, std::vector<int>, std::less<int>>cities, std::priority_queue<int, std::vector<int>, std::less<int>>defenders) {
    int sol = 0;
    while (!cities.empty()) {
        if (cities.top() > defenders.top()) { // city can not be defended
            cities.pop();
        }
        else {
            cities.pop();
            defenders.pop();
            sol++;
        }
    }
    return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int size;
    std::cin >> size;
    if (!std::cin)
        return false;

    std::priority_queue<int,std::vector<int>, std::less<int>>cities;
    std::priority_queue<int, std::vector<int>, std::less<int>>defenders;

    int aux;
    for (int i = 0; i < size; i++) {
        std::cin >> aux;
        cities.push(aux);
    }
    for (int i = 0; i < size; i++) {
        std::cin >> aux;
        defenders.push(aux);
    }

    std::cout << solve(cities, defenders) << "\n";
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