#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include "Matriz.h"

const int infinite = 1e9;
struct chest {
    int depth;
    int gold;
};

/*

solve(i, p) = maxima cantidad de oro que se puede conseguir con i cofres y p segundos bajo el agua

solve(i, p) = solve(i-1, p) si profundidad[i] + 2*profundidad[i] > p
              max(solve(i-1, p), solve(i-1, p - profundidad[i] + 2*profundidad[i]) + oro[i])

solve(0, p) = 0
solve(i, 0) = 0

*/

std::pair<int, int> solve(int time, std::vector<chest> chests, std::vector<bool>& chosen) {

    Matriz<int> matrix(chests.size(), time + 1);
    int cur_depth, cur_gold, max_gold, max_chests = 0;
    matrix[0][0] = 0;

    for (int i = 1; i <= chests.size() - 1; i++) {
        matrix[i][0] = 0;
        for (int j = 1; j <= time; j++) {
            matrix[0][j] = 0;

            cur_depth = chests[i].depth + (2 * chests[i].depth);
            cur_gold = chests[i].gold;

            if (cur_depth > j) {
                matrix[i][j] = matrix[i - 1][j];
            }
            else {
                matrix[i][j] = std::max(matrix[i - 1][j], matrix[i - 1][j - cur_depth] + cur_gold);
            }
        }
    }

    max_gold = matrix[chests.size() - 1][time];
    for (int i = chests.size() - 1; i > 0; i--) {
        if (matrix[i][time] == matrix[i - 1][time]) {
            chosen[i] = false;
        }
        else {
            chosen[i] = true;
            max_chests++;
            time -= chests[i].depth + 2 * chests[i].depth;
        }
    }
    return { max_gold, max_chests };
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int time, ch, d, g;
    std::cin >> time;

    if (!std::cin)
        return false;

    std::cin >> ch;
    std::vector<chest> chests(ch + 1);
    std::vector<bool> chosen(ch + 1);
    for (int i = 1; i <= ch; i++) {
        std::cin >> d >> g;
        chests[i] = { d, g };
    }

    auto it = solve(time, chests, chosen);

    std::cout << it.first << "\n";
    std::cout << it.second << "\n";

    for (int i = 0; i < chosen.size(); i++) {
        if (chosen[i]) {
            chest ch = chests[i];
            std::cout << ch.depth << " " << ch.gold << "\n";
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