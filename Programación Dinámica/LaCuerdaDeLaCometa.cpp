#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"

struct lace {
    int length;
    int cost;
};

const int infinite = 1e9;

/*
    cost(i,j) = cost(i-1,j) if li>j
                std::min(cost(i-1, j-li) + Ci, cost(i-1, j))
*/
int cost(std::vector<lace>& strings, const int& length) {
    int n = strings.size() - 1;
    std::vector<int> cost(length + 1, infinite);
    cost[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = length; j >= strings[i].length; j--) {
            cost[j] = std::min(cost[j - strings[i].length] + strings[i].cost, cost[j]);
        }
    }
    return cost[length];
}

/*
    minimun(i,j) = minimun(i-1,j) if li>j
                   std::min(minimin(i-1, j-li) + 1, minimun(i-1, j))
*/
int minimun(std::vector<lace>const& strings, int length) {

    int n = strings.size() - 1;
    std::vector<int> min (length + 1, infinite);
    min[0] = 0;

    for (int i = 1; i <= n; i++) {
        for (int j = length; j >= strings[i].length; j--) {
            min[j] = std::min(min[j], min[j - strings[i].length] + 1);
        }
    }
    return min[length];
}
/*
    ways(i,j) = ways(i-1,j) if li>j
                ways(i-1,j-li) + ways(i-1,j)
    ways(i,0) = 1
    ways(0,j) = 0
*/
int64_t ways(std::vector<lace>const& strings, int length) {

    int n = strings.size() - 1;
    std::vector<int64_t> num(length + 1);
    num[0] = 1;

    for (int i = 1; i <= n; i++) {
        for (int j = length; j >= strings[i].length; j--) {
            num[j] = num[j - strings[i].length] + num[j];
        }
    }
    return num[length];
}
/*
    able(i,j) = able(i-1,j) if li>j
                able(i-1, j-li) || able(i-1,j) if li<=j
*/
bool able(std::vector<lace>const& strings, int length) {

    int n = strings.size() - 1;
    std::vector<bool> possible(length + 1);
    possible[0] = true;

    for (int i = 1; i <= n; i++) {
        for (int j = length; j >= strings[i].length; j--) {
            possible[j] = possible[j - strings[i].length] || possible[j];
        }
    }
    return possible[length];
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {

    int num_strings, length;
    std::cin >> num_strings >> length;
    if (!std::cin)
        return false;

    std::vector<lace> strings(num_strings+1);
    lace aux;
    
    for (int i = 1; i <= num_strings; i++) {
        std::cin >> aux.length >> aux.cost;
        strings[i] = aux;
    }
    
    if (!able(strings,length)) {
        std::cout << "NO\n";
    }
    else {
        std::cout << "SI" << " " << ways(strings, length) << " " << minimun(strings, length) << " " << cost(strings, length) << "\n";
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