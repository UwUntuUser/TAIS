// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include"Grafo.h"



// el problema se resume en calcular la componente conexa mas grande el grafo
class grafo_amigo {

private:
    std::vector<bool> visitados;
    std::vector<int> anterior;
    int tamanio;
    int mayor;

    void componente(Grafo const& g, int v) {

        visitados[v] = true;
        for (int vertice : g.ady(v)) {
            if (!visitados[vertice] && anterior[v] != vertice)
            {
                tamanio++;
                componente(g, vertice);
            }
        }
    }

public:
    grafo_amigo(Grafo& g) :visitados(g.V(), false), anterior(g.V()), mayor(0), tamanio(0) {

        for (int i = 0; i < g.V(); i++)
            if (!visitados[i])
            {
                tamanio = 1;
                componente(g, i);
                mayor = (tamanio > mayor) ? tamanio : mayor;
            }
    };

    int mayor_grupo() {
        return mayor;
    }
};


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada

    int v, a;
    std::cin >> v >> a;
    
    Grafo g(v);
    int ini,fin;

    while (a--) {
        std::cin >> ini >> fin;
        g.ponArista(ini - 1, fin - 1);
    }

    grafo_amigo amigos(g);

    std::cout << amigos.mayor_grupo() << "\n";

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}