#include <iostream>
#include <iomanip>
#include <fstream>
#include"PriorityQueue.h"

struct caja {
    int numero;
    int tiempoOcupada;
};

bool operator<(caja const& a, caja const& b){

    return (a.tiempoOcupada < b.tiempoOcupada) || (a.tiempoOcupada == b.tiempoOcupada && a.numero < b.numero);
}

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int cajas, clientes;
    std::cin >> cajas >> clientes;

    if (cajas == 0 && clientes == 0)
        return false;

    PriorityQueue<caja, std::less<caja>> cola;

    for (int i = 0; i < cajas; i++)
        cola.push({ i + 1,0 });

    while (clientes > 0) {
 
        caja aux = cola.top();
        cola.pop();

        if (cajas > 0) {
            std::cin >> aux.tiempoOcupada;
            cola.push(aux);
            cajas--;
        }
        else {
            int tiempo;
            std::cin >> tiempo;
            aux.tiempoOcupada += tiempo;
            cola.push(aux);
        }
        clientes--;
    }

    std::cout << cola.top().numero << "\n";
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
