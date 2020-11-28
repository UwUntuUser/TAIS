// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include<limits>
#include"DigrafoValorado.h"
#include"IndexPQ.h"


const int INF = 100000000000;

class package_delivery {

private:
    IndexPQ<int> q;
    std::vector<int> distance;
    int cost;
    bool is_possible;
    void djkstra(DigrafoValorado<int>& g, int start) {

        distance[start] = 0;
        q.push(start, 0);
        while (!q.empty()) {
            auto it = q.top();
            q.pop();
            for (auto ady : g.ady(it.elem)) {
                relajar(ady);
            }
        }
    }

    void relajar(AristaDirigida<int> a) {

        int v = a.desde();
        int w = a.hasta();
        if (distance[w] > distance[v] + a.valor()) {
            distance[w] = distance[v] + a.valor();
            q.update(w, distance[w]);
        }
    }
    void updateDistances() {
        for (int i = 0; i < distance.size(); i++) {
            distance[i] = INF;
        }
    }
    
public:
    package_delivery(DigrafoValorado<int>& g, int start, std::vector<int> ps):distance(g.V(),INF), q(g.V()),cost(0),is_possible(true) {
        
        djkstra(g, start);
        for (int p : ps) { 
            if (distance[p] >= INF)
                is_possible = false;
            cost += distance[p];
        }
        // una vez sepa que puedo ir a todas las casas, quiero saber si puedo volver de ellas
        if (is_possible) {
            updateDistances();
            DigrafoValorado<int> a = g.inverso();
            djkstra(a, start);
            for (int p : ps) {
                if (distance[p] >= INF)
                    is_possible = false;
                cost += distance[p];
            }
        }
    }

    bool possible(std::vector<int> pk) {
        return is_possible;
    }

    int totalCost() {
        return cost;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    DigrafoValorado<int> graph(std::cin, 1);
    if (!std::cin)
        return false;

    int start, num_packages, aux;
    std::cin >> start >> num_packages;
    std::vector<int>packages(num_packages);
    for (int i = 0; i < num_packages; i++) {
        std::cin >> aux;
        packages[i] = aux - 1;
    }

    package_delivery pd(graph, start-1, packages);

    if (pd.possible(packages)) {
        std::cout << pd.totalCost()<<"\n";
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