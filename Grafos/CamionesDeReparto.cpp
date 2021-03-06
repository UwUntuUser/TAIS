// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include"GrafoValorado.h"


class truks {

private:
    std::vector<bool>visited;
    bool possible;

    void dfs(GrafoValorado<int>& g, int ini, int end, int value) {

        visited[ini] = true;
        for (auto a : g.ady(ini)) {
            if (!visited[a.otro(ini)]) {
                if (a.valor() >= value) {// we can cross
                    if (a.otro(ini) == end) {
                        possible = true;
                    }
                    dfs(g, a.otro(ini), end, value);
                }
            }
        }
    }
public:

    truks(GrafoValorado<int>& g, int ini, int end, int value) : visited(g.V()), possible(false) {
        dfs(g, ini, end, value);
    }

    bool is_possible() {
        return possible;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    GrafoValorado<int> g(std::cin, 1);
    if (!std::cin)
        return false;
    
    int queries;
    std::cin >> queries;
    int ini, end, value;
    while (queries--) {
        std::cin >> ini >> end >> value;
        truks t(g, ini - 1, end - 1, value);
        if (t.is_possible()) {
            std::cout << "SI\n";
        }
        else
            std::cout << "NO\n";
    }

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