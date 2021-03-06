#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include<algorithm>


int solve(std::vector<int> &v, int voltage) {

    int start = 0;
    int end = v.size() - 1;
    int sol = 0;
    std::sort(v.begin(), v.end());
    
    while (start < end) {
        if (v[start] + v[end] >= voltage) {
            start++;
            end--;
            sol++;
        }
        else {
            start++;
        }
    }
    return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {

    int batteries, voltage;
    std::cin >> batteries >> voltage;

    std::vector<int> v(batteries);
    int aux;
    for (int i = 0; i < batteries; i++) {
        std::cin >> aux;
        v[i] = aux;
    }

    std::cout << solve(v,voltage) << "\n";
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}