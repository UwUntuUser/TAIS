#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include "Matriz.h"

struct monedas {
    int valor;
    int cantidad;
};
const int infinito = 1e9;

/*
    solve(v, coche) = numero minimo de monedas que podemos usar para pagar coche con v monedas
    solve(v, coche) = solve(v-1, coche) si valor[v] > coche
                      min(solve(v-1, coche), solve(v-1, coche - valor[v]) + 1) si valor[v] < coche

    solve(0, coche) = 0 
    solve(v, 0) = 0

*/

int solve(std::vector<monedas>const& v, int coche) {

    Matriz<int> matriz(v.size() + 1, coche + 1, infinito);
    matriz[0][0] = 0;

    for (int i = 1; i <= v.size(); i++) { // recorrer los distintos tipos de monedas
        matriz[i][0] = 0;
        for (int j = 1; j <= coche; j++) { // recorrer el precio de coche
            matriz[i][j] = matriz[i - 1][j];

            if (j >= v[i - 1].valor) {
                int aux;
                int k = 1;
                
                while (k <= v[i - 1].cantidad && j - k * v[i - 1].valor <= coche && j - k * v[i - 1].valor >= 0) { 
                    // recorrer la cantidad de monedas del tipo i
                    aux = matriz[i - 1][j - k * v[i - 1].valor] + k;
                    if (aux < matriz[i][j]) {
                        matriz[i][j] = aux;
                    }
                    k++;
                }
            }
        }
    }
    return matriz[v.size()][coche];
}

bool mayor(const monedas& a, const monedas& b) {
    return a.valor > b.valor;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int size;
    std::cin >> size;
    if (!std::cin)
        return false;

    int coche;
    std::vector<monedas> v(size);
    
    for (int i = 0; i < size; i++) {
        std::cin >> v[i].valor;
    }
    for (int i = 0; i < size; i++) {
        std::cin >> v[i].cantidad;
    }
    std::cin >> coche;
    std::sort(v.begin(), v.end(), mayor);

    int sol = solve(v, coche);

    if (sol == infinito) {
        std::cout << "NO\n";
    }
    else {
        std::cout << "SI " << sol << "\n";
    }
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