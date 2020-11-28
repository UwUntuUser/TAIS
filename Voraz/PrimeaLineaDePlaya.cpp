// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include<vector>

struct building {
    int start;
    int end;
};
bool operator<(building const& a, building const& b) {
    return b.end < a.end;
}

int solve(std::priority_queue<building> &q) {
    int tunels = 1;
    int n = q.size() - 1;
    auto it = q.top();
    q.pop();
    while (n--) {
        if (it.end <= q.top().start) {
            tunels++;
            it = q.top();
        }
        q.pop();
    }
    return tunels;
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num_buildings;
    std::cin >> num_buildings;
    if (num_buildings == 0)
        return false;

    std::priority_queue<building> q;
    int s, e;
    while (num_buildings--) {
        std::cin >> s >> e;
        q.push({ s,e });
    }

    std::cout << solve(q) << "\n";
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
