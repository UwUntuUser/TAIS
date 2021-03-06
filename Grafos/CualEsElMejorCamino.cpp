#include <iostream>
#include <iomanip>
#include <fstream>
#include <queue>
#include <vector>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

const int infinite = 1e9;

class BFS {

private:
    std::vector<bool> visited;
    std::vector<int> distances;

public:
    BFS(DigrafoValorado<int> g, int ini, int end) :visited(g.V(),false), distances(g.V(),infinite) {

        distances[ini] = 0;
        visited[ini] = true;
        std::queue<int>q;
        q.push(ini);
        while(!q.empty()){
            int v = q.front();
            q.pop();
            for (auto w : g.ady(v)) {
                if (!visited[w.hasta()]) {
                    q.push(w.hasta());
                    visited[w.hasta()] = true;
                    distances[w.hasta()] = distances[v] + 1;
                }
            }
        }
    }
    int distance(int v) {
        return distances[v];
    }
};

class DTA {

private:
    std::vector<bool> visited;
    std::vector<int> distances;
    std::vector<int>costs;
    IndexPQ<int> q;

    void relax(AristaDirigida<int> a) {

        int v = a.desde();
        int w = a.hasta();
        if (costs[w] > costs[v] + a.valor()) {
            costs[w] = costs[v] + a.valor();
            q.update(w, costs[w]);
            distances[w] = distances[v] + 1;
        }
    }
public:
    DTA(DigrafoValorado<int> g, int ini, int end) :visited(g.V()), distances(g.V(), infinite), q(g.V()), costs(g.V(),infinite) {
    
        distances[ini] = 0;
        costs[ini] = 0;
        visited[ini] = true;
        q.push(ini,0);
        while (!q.empty()) {
            int v = q.top().elem;
            q.pop();
            for (auto a : g.ady(v)) {
                relax(a);
            }
        }
    }

    int distance(int v) {
        return distances[v];
    }
    int cost(int v) {
        return costs[v];
    }
};

bool resuelveCaso() {

    int v, a;
    std::cin >> v >> a;
    
    if (!std::cin)
        return false;

    DigrafoValorado<int> g(v);
    int ini, end, value;
    while (a--) {
        std::cin >> ini >> end >> value;
        g.ponArista({ ini - 1,end - 1,value });
        g.ponArista({ end - 1,ini - 1,value });
    }

    int query;
    std::cin >> query;
    while (query--) {
        std::cin >> ini >> end;
        BFS gBFS(g, ini - 1, end - 1);
        DTA gDTA(g, ini - 1, end - 1);
        
        if (gBFS.distance(end - 1) != infinite) {
            std::cout << gDTA.cost(end - 1) << " ";
            if (gBFS.distance(end - 1) == gDTA.distance(end - 1)) {
                std::cout << "SI\n";
            }
            else {
                std::cout << "NO\n";
            }
        }
        else {
            std::cout << "SIN CAMINO\n";
        }
    }
    std::cout << "---\n";


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