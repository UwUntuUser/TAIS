#include <iostream>
#include <iomanip>
#include <fstream>
#include "Matriz.h"

/*
subsecuence(i, j) = longuitud de la palabra común mas larga 

subsecuence(i, j) = subsecuence(i-1, j-1) +1 si p1[i]==p2[j] 
                    max(subsecuence(i-1, j), subsecuence(1, j-1))

subsecuence(i, 0) = 0 
subsecuence(0, 1) = 0
*/

int subsecuence(std::string& word1, std::string& word2,int i, int j, Matriz<int>& matrix) {
    
    if (i < 0 || j < 0)
        return 0;
    int& res = matrix[i][j];
    if (res == -1) {
        if (word1[i] == word2[j]) {
            res = subsecuence(word1, word2, i - 1, j - 1, matrix) + 1;
        }
        else {
            res = std::max(subsecuence(word1, word2, i - 1, j, matrix), 
                        subsecuence(word1, word2, i, j - 1, matrix));
        }
    }
    return res;
}

std::string build(std::string const& word1, std::string const& word2, Matriz<int>& matrix, int i, int j) {
    
    if (matrix[word1.length() - 1][word2.length() - 1] == 0)
        return {};
    if (i < 0 || j < 0)
        return{};
    if (word1[i] == word2[j])
        return build(word1, word2, matrix, i - 1, j - 1) + word1[i];
    else if (matrix[i][j] == matrix[i][j - 1])
        return  build(word1, word2, matrix, i, j - 1);
    else
        return build(word1, word2, matrix, i - 1, j);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    std::string word1, word2;
    std::cin >> word1 >> word2;
    if (!std::cin)
        return false;

    int i = word1.length() - 1;
    int j = word2.length() - 1;

    Matriz<int> matrix(i + 1, j + 1, -1);

    subsecuence(word1, word2, i, j, matrix);
    std::cout << build(word1, word2, matrix, i, j) << "\n";

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