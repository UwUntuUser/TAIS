// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<deque>
#include"Digrafo.h"

class tasks {

private:

    std::vector<bool> visited;
    std::deque<int> _q;
    std::vector<bool> stacked;
    bool possible;


    void dfs(Digrafo const& g, int v) {
        visited[v] = true;
        stacked[v] = true;

        for (int w : g.ady(v)) {
            if (!possible) {
                return;
            }
            if (!visited[w]) {
                dfs(g, w);
            }
            else if (stacked[w]) {
                    possible = false;
            }
        }
        _q.push_front(v);
        stacked[v] = false;
    }

public:

    tasks(Digrafo& g) : visited(g.V(), false), possible(true), stacked(g.V()) {
        for (int i = 0; i < g.V(); i++) {
            if (!visited[i]) {
                dfs(g, i);
            }
        }
    };

    std::deque<int>& order() {
        return _q;
    }

    bool is_possible() {
        return possible;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    Digrafo g(std::cin, 1);

    if (!std::cin)
        return false;

    tasks t(g);

    if (t.is_possible()) {
        for (int task : t.order()) {
            std::cout << task + 1 << " ";
        }
        std::cout << "\n";
    }
    else
        std::cout << "Imposible\n";


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