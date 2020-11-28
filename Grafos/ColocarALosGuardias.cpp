// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include<algorithm>
#include"Grafo.h"


class colocarGuardias {
private:

    std::vector<bool> visitados;
    std::vector<bool>coloreados;
    int num_minimo;
    int num_trues;
    int num_falses;
    bool bipartito;

    bool dfs(Grafo const& g, int v) {

        visitados[v] = true;
        for (int w : g.ady(v)) {
            if (!visitados[w] && bipartito) {

                coloreados[w] = !coloreados[v];
                num_falses = (coloreados[w]) ? num_falses : ++num_falses;
                num_trues = (coloreados[w]) ? ++num_trues : num_trues;
                bipartito = dfs(g, w);
            }
            else if (coloreados[w] == coloreados[v]) {// no es bipartito
                bipartito = false;
            }
        }
        return bipartito;
    }
public:
    colocarGuardias(Grafo const& g) : visitados(g.V(),false), num_minimo(0),num_trues(0),num_falses(0), bipartito(true), coloreados(g.V()){
        for (int i = 0; i < g.V();i++)
        {
            if (!visitados[i] && bipartito) {

                coloreados[i] = true;
                num_trues++;
                bipartito = dfs(g, i);
                num_minimo += std::min(num_falses, num_trues);

                num_trues = num_falses = 0;
            }
        }
    };
    int minimo() const{
        return num_minimo;
    }
    bool esPosible() const{
        return bipartito;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int v, a;
    std::cin >> v >> a;
    if (!std::cin)
        return false;

    Grafo g(v);
    int ini, fin;

    while (a--) {
        std::cin >> ini >> fin;
        g.ponArista(ini - 1, fin - 1);
    }

    colocarGuardias guardias(g);

    if (guardias.esPosible())
        std::cout << guardias.minimo() << "\n";
    else
        std::cout << "IMPOSIBLE\n";

    return true;
}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    while (resuelveCaso());


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}