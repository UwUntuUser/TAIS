#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"
#include <vector>

/*
bombillas(i,p) coste minimo de instalar i bombillas para una potencia p

bombillas(i, p) = bombillas(i-1, p)                 if(power[i] > p)
                  bombillas(i, p-p[i]) + cost[i]    if(power[i] < p)

bombillas(0, p) = infinite
bombillas(i, 0) = 0
*/

const int infinite = 1e9;
std::pair<int, int> solve(int bulbs, int pMin, int pMax, std::vector<int> power, std::vector<int> cost) {

    Matriz<int> matrix(bulbs + 1, pMax + 1, infinite);
    matrix[0][0] = 0;
    for (int i = 1; i <= bulbs; i++) {
        matrix[i][0] = 0;
        for (int j = 1; j <= pMax; j++) {
            if (power[i] > j) {
                matrix[i][j] = matrix[i - 1][j];
            }
            else {
                matrix[i][j] = std::min(matrix[i - 1][j], matrix[i][j - power[i]] + cost[i]);
            }
        }
    }

    int p = pMin, cMin = matrix[bulbs][pMin];
    for (int i = pMin; i <= pMax; i++) {
        if (cMin > matrix[bulbs][i]) {
            cMin = matrix[bulbs][i];
            p = i;
        }
    }
    return { cMin, p };
}

bool resuelveCaso() {

    int lBulbs, pMin, pMax, aux;
    std::cin >> lBulbs >> pMax >> pMin;
    if (!std::cin)
        return false;

    std::vector<int> power(lBulbs + 1);
    std::vector<int> cost(lBulbs + 1);

    for (int i = 1; i <= lBulbs; i++) {
        std::cin >> power[i];
    }
    for (int i = 1; i <= lBulbs; i++) {
        std::cin >> cost[i];
    }

    auto sol = solve(lBulbs, pMin, pMax, power, cost);
    if (sol.first == infinite) {
        std::cout << "IMPOSIBLE\n";
    }
    else {
        std::cout << sol.first << " " << sol.second << "\n";
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