
#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <queue>
#include "Matriz.h"

const int infinite = 1e9;

/*
solve(i,j) = numero minimo de dardos para conseguir j puntos con i secciones

solve(i,j) = solve(i-1, j) si j < seccion[i]
             min(solve(i-1, j-seccion[i]) + 1 , solve(i-1, j)) si j>seccion[i]

seccion(i,0) = 0
seccion(0,j) = 0
*/
std::priority_queue <int> solve(std::vector<int> const& sections, int points) {

    
    int n = sections.size() - 1;
    Matriz<int>matrix(n + 1, points + 1, infinite);
    matrix[0][0] = 0;

    for (int i = 1; i <= n; i++) {
        matrix[i][0] = 0;
        for (int j = 1; j <= points; j++) {
            if (sections[i] > j) {
                matrix[i][j] = matrix[i - 1][j];
            }
            else {
                matrix[i][j] = std::min((matrix[i][j - sections[i]]) + 1, matrix[i - 1][j]);
            }
        }
    }
    int tpoints;
    int i = n, j = points;
    std::priority_queue<int> q;
    if (matrix[n][points] != infinite) {
        while (j > 0) {
            if (sections[i] < j && matrix[i][j] != matrix[i - 1][j]) {
                q.push(sections[i]);
                j -= sections[i];
            }
            else
                i--;
        }
    }
    return q;
}

bool resuelveCaso() {

    int points, nsections;
    std::cin >> points >> nsections;
    
    if (!std::cin)
        return false;
    
    std::vector<int> sections(nsections + 1, 0);
    for (int i = 1; i <= nsections; i++) {
        std::cin >> sections[i];
    }

    std::priority_queue<int>q = solve(sections, points);
    if (q.empty()) {
        std::cout << "Imposible\n";
    }
    else {
        int n = q.size();
        std::cout << n << ": ";
        for (int a = 0; a < n; a++) {
            std::cout << q.top();
            q.pop();
        }
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