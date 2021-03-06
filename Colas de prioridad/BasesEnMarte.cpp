
#include <iostream>
#include <fstream>
#include <queue>
#include <deque>
using namespace std;


struct pila {
    int id;
    int cargaA;
    int cargaMax;
};

bool operator < (pila const& pila1, pila const& pila2) {
    if (pila1.cargaMax < pila2.cargaMax) {
        return true;
    }
    else if (pila1.cargaMax == pila2.cargaMax) {
        return pila1.id < pila2.id;
    }
}

bool resuelveCaso() {

    int numPilas, aux, id = 1, recargas, perdida, consulta;
    std::cin >> numPilas;
    if (!std::cin)  // fin de la entrada
        return false;

    priority_queue<pila, vector<pila>, less<pila>> pilas;
    deque<int> repuesto;

    while (numPilas--) {
        std::cin >> aux;
        pilas.push({ aux, aux,id });
    }
    std::cin >> recargas;
    while (recargas--) {
        std::cin >> aux;
        repuesto.push_back(aux);
    }

    std::cin >> perdida >> consulta;



    // resolver el caso posiblemente llamando a otras funciones

    // escribir la solución

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
