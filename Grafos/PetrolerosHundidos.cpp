// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include<string>
#include"ConjuntosDisjuntos.h"
#include<algorithm>

using Map = std::vector<std::string>;

class sunken_tankers {

private:

    std::vector<std::pair<int, int>> join_directions = { {-1,-1},{-1,0},{-1,1},{0,-1},{0,1},{1,-1},{1,0},{1,1} }; // clockwise order
    std::vector<std::pair<int, int>> directions = { {1, 0}, { -1,0 }, { 0,1 }, {0,-1} }; // down, up, right, left
    std::vector<std::vector<bool>>visited;
    int rows;
    int columns;
    int max_stain;


    int dfs(ConjuntosDisjuntos& set, Map const& map, int x, int y) {
       
        int size = 1;
        visited[x][y] = true;
        for (auto it : directions) {
            int new_x = x + it.first;
            int new_y = y + it.second;
            if (correct(new_x, new_y) && map[new_x][new_y] == '#' && !visited[new_x][new_y]) {
                // set is a vector of (row*colum) size, given 2 coordinates (x,y) we can calculate te position in set vector this way
                int point1 = x * columns + y;
                int point2 = new_x  * columns + new_y;
                set.unir(point1, point2);
                size += dfs(set, map, new_x, new_y);
            }
        }
        return size;
    }
    bool correct(int x, int y) {
        return (x >= 0 && x < rows && y >= 0 && y < columns);
    }
public:

    sunken_tankers(ConjuntosDisjuntos &set,Map const&map, int vertix, int edges): visited(vertix,std::vector<bool>(edges,false)), rows(vertix), columns(edges),max_stain(0) {
        
        for (int i = 0; i < vertix; i++) {
            for (int j = 0; j < edges; j++) {
                if (map[i][j] == '#' && !visited[i][j]) // new tree set, dfs to build disjoint set
                    max_stain = std::max(max_stain, dfs(set, map, i, j));
            }
        }
    }

    void join(Map const&map,ConjuntosDisjuntos& set, int x, int y) {
        
        int ini = (x) * columns + y;
        for (auto it : join_directions) {
            int nx = x + it.first;
            int ny = y + it.second;
            if (correct(nx,ny)) {
                if (map[nx][ny] == '#') { // separacion de if necesaria
                    int end = nx * columns + ny;
                    set.unir(ini, end);
                }
            }
        }
        max_stain = std::max(max_stain, set.cardinal(ini));
    }

    int max_size() {
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
    ConjuntosDisjuntos tankers(vertix * edges);

    std::string trash;
    std::getline(std::cin, trash);
    for (std::string& line : map) {
        std::getline(std::cin, line);
    }
    sunken_tankers tanks(tankers, map, vertix, edges);

    int queries, x, y;
    std::cin >> queries;

    std::cout << tanks.max_size() << " ";
    while (queries--) {
        std::cin >> x >> y;
        tanks.join(map, tankers, x -1, y-1);
        std::cout << tanks.max_size() << " ";
    }
    std::cout << "\n";

    
    


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