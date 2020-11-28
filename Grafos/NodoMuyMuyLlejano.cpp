// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<queue>
#include<vector>
#include"Grafo.h"

class far_node {

private:

    std::vector<bool> visited;
    std::vector<int>distance;
    int num_nodes;

    void bfs(Grafo const& g, int start, int ttl) {
        
        std::queue<int>q;
        q.push(start);
        visited[start] = true;
        distance[start] = 0;
        
        while (!q.empty()) {

            auto it = q.front();
            q.pop();
            for (auto a : g.ady(it)) { // visitar adyacentes
                if (!visited[a] && distance[it]+1<=ttl)
                {
                    q.push(a);
                    visited[a] = true;
                    distance[a] = distance[it] + 1;
                    num_nodes++;
                }
            }
        }
        num_nodes = g.V() - num_nodes;
    }

public:

    far_node(Grafo& g, int start, int ttl) :visited(g.V(), false),num_nodes(1),distance(g.V()) {
    
        bfs(g, start,ttl);
    };

    int num_computers() {
        return num_nodes;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    Grafo g(std::cin, 1);

    if (!std::cin)
        return false;

    int queries;
    std::cin >> queries;
    
    int start, ttl;

    while (queries--) {
        
        std::cin>>start>>ttl;
        far_node nodes(g, start-1, ttl);
        std::cout << nodes.num_computers() << "\n";
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