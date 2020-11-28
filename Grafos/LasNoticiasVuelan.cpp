// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include<queue>
#include"Grafo.h"


class news {

private:
    std::vector<bool>visited;
    std::queue<int> _queue;
    std::vector<int>sizes;
    int tam;

    void update_sizes() {

        while (!_queue.empty())
        {
            auto it = _queue.front();
            _queue.pop();
            sizes[it] += tam;
        }
    }

    void dfs(Grafo const&g, int v) {

        visited[v] = true;
        _queue.push(v);

        for (int w : g.ady(v)) {
            if (!visited[w]) {
                tam++;
                dfs(g, w);
            }
        }
    }
public:
    
    news(Grafo& g) :visited(g.V()),sizes(g.V(),1), tam(1) {
    
        for (int v = 0; v < g.V(); v++) {

            if (!visited[v]) {
                tam = 0;
                dfs(g, v);
                update_sizes();
                tam = 0;
            }
        }
    };

    std::vector<int>& get_sizes() {
        return sizes;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int vertices, edges;
    std::cin >> vertices >> edges;
    if (!std::cin)
        return false;
    
    Grafo g(vertices);

    int size, start, end;

    while (edges--) {
        std::cin >> size;
        if (size > 0){
            std::cin >> start;
            for (int i = 1; i < size; i++)
            {
                std::cin >> end;
                g.ponArista(start - 1, end - 1);
            }
        }
    }

    news n(g);

    for (int a : n.get_sizes())
        std::cout << a << " ";
    std::cout << "\n";


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