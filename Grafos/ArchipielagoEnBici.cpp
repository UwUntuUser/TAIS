// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include"GrafoValorado.h"
#include<vector>
#include"PriorityQueue.h"

bool operator<(std::pair<int, int>a, std::pair<int, int>b) {
    return a.second < b.second;
}
class archipelago {

private:
    std::vector<bool>visited;
    int nodesVisited;
    int numNodes;
    int c;

    void prim(GrafoValorado<int>const& g, int start) {
        PriorityQueue<std::pair<int, int>>q;
        int numNodes = 0;
        q.push({ c, start});

        while (!q.empty() && numNodes<g.V()) {
            auto it = q.top(); q.pop();
            if (!visited[it.second]) {
                c += it.first;
                visited[it.second] = true;
                numNodes++;
                for (auto ady : g.ady(it.second)) {
                    if (!visited[ady.otro(it.second)]) {
                        q.push({ ady.valor(),ady.otro(it.second) });
                    }
                }
            }
        }
    }
    
public:

    archipelago(GrafoValorado<int> const&g):visited(g.V()),numNodes(g.V()),nodesVisited(0),c(0) {
        prim(g,0);
    }

    bool possible() {
        for (bool ok : visited)
            if (!ok) return false;
        return true;
    }
    int cost() {
        return c;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    GrafoValorado<int> g(std::cin, 1);
    if (!std::cin)
        return false;

    archipelago a(g);
    if (a.possible()) {
        std::cout << a.cost() << "\n";
    }
    else
        std::cout << "No hay puentes suficientes\n";


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