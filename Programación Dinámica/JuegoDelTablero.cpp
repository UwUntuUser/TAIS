#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"

struct tSol {
    int sum;
    int start;
};

void refactor(Matriz<int> &board, int N) {

    for (int i = 1; i < N; i++) {
        for (int j = 1; j <= N; j++) {
            board[i][j] = std::max(board[i - 1][j - 1], std::max(board[i - 1][j], board[i - 1][j + 1])) + board[i][j];
        }
    }
}

tSol solve(Matriz<int> const& board, int N) {
    
    tSol sol = { 0,0 };
    for (int i = 1; i <= N; i++) {
        if (sol.sum < board[N - 1][i]) {
            sol.sum = board[N - 1][i];
            sol.start = i;
        }
    }
    return sol;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    
    int dimensions;
    std::cin >> dimensions;
    if (!std::cin)
        return false;

    Matriz<int> board(dimensions, dimensions + 2, 0);

    for (int i = 0; i < dimensions; i++) {
        for (int j = 1; j <= dimensions; j++) {
            std::cin >> board[i][j];
        }
    }

    refactor(board, dimensions);
    tSol sol = solve(board,dimensions);
    std::cout << sol.sum << " " << sol.start << "\n";
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