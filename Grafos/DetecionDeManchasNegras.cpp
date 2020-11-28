// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include<algorithm>
#include"Grafo.h"


using Map = std::vector<std::string>;

class black_stain {

    std::vector<std::vector<bool>>visited;
    std::vector<std::pair<int, int>> directions = { {1, 0}, { -1,0 }, { 0,1 }, {0,-1} }; // down, up, right, left
    int rows;
    int columns;
    int num_stain;
    int max_stain;


    bool correct(int x, int y) {
        return (x >= 0 && x < rows && y >= 0 && y < columns);
    }

    int dfs(Map const& map, int x, int y) {
        
        int size = 1;
        visited[x][y] = true;
        for (auto direction : directions) {
            int new_x = x + direction.first;
            int new_y = y + direction.second;
            if (correct(new_x, new_y) && map[new_x][new_y] == '#' && !visited[new_x][new_y]) { // if new coordenate is in map and is stained
                size += dfs(map, new_x, new_y);
            }
        }
        return size;
    }

public:

    black_stain(Map const&map, const int row, const int column):visited(row, std::vector<bool>(column,false)), rows(row), columns(column), num_stain(0), max_stain(0) {
        
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < columns; j++) {
                if (map[i][j] == '#' && !visited[i][j]) {     // if stain, look for near stains
                    num_stain++;
                    max_stain = std::max(max_stain,dfs(map, i, j));
                }
            }
        }
    }

    int num_stains() {
        return num_stain;
    }

    int max_stains() {
        return max_stain;
    }
};




// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int vertix, edges;
    std::cin >> vertix >> edges;

    if (!std::cin)
        return false;

    Map map(vertix);
    for (int i = 0; i < vertix; i++) {
        std::cin >> map[i];
    }

    black_stain detection(map, vertix, edges);

    std::cout << detection.num_stains() << " " << detection.max_stains() << "\n";


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