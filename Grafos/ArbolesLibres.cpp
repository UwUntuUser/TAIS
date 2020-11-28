// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include"Grafo.h"

class arbol_libre {

private :
    std::vector<bool> visitados;
    std::vector<int> anteriores;
    bool libre;

    bool es_conexo() {
        bool conexo = true;
        for (int i = 0; i < visitados.size(); i++)
            if (!visitados[i])
                conexo = false;
        return conexo;
    }

public:

    arbol_libre(Grafo const& g, bool l) :visitados(g.V(),false),anteriores(g.V()), libre(l) {
        libre = sin_ciclos(g,0);
    }

    bool sin_ciclos(Grafo const&g ,int v) {
        
        bool libre = true;
        visitados[v] = true;
        
        for (int ady : g.ady(v))
            if (ady != anteriores[v] && libre)
            {
                if (!visitados[ady])
                {
                    anteriores[ady] = v;
                    libre =sin_ciclos(g, ady);
                }
                else
                    libre = false;
            }
        return libre;
    }

    bool es_libre() {
        return libre && es_conexo();
    }

};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int vertices, aristas;
    std::cin >> vertices >> aristas;
    if (!std::cin)
        return false;


    Grafo g(vertices);
    
    int a, b;
    while (aristas--) {
        std::cin >> a >> b;
        g.ponArista(a, b);
    }

    bool libre = true;
    arbol_libre arbol(g,true);

    if (arbol.es_libre())
        std::cout << "SI\n";
    else
        std::cout << "NO\n";


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