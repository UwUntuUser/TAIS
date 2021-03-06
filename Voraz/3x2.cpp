#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Primeramente se leen los datos de entrada en una cola de prioridad ordenada de mayor a menor precio, asi maximizamos el ahorro

 Se recorre secuencialmente los elementos y cuando este en una posicion multiplo de 3, aumento la cantidad ahorrada sumando 
 el valor del libro mas prioritario en ese momento.

 La posicion multiplo de 3 se calcula con (i+1) % 3 == 0:
 Se suma 1 ya que las posiciones en listas, vectores y similares empiezan en 0 y no en 1(las posiciones multiplos de 3 serian 2-5-8... y queremos 3-6-9...)

 Siendo N el numero de libros:
 El coste de isertar elementos en la cola de prioridad es del orden de O(N log N)
 El coste de calcular el ahorro conseguido es del orden de O(N log N) debido a la operacion pop()
 EL coste total del ejercicio es del orden de O(N log N)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    int nlibros, aux, ahorrado = 0;
    std::cin >> nlibros;
    if (!std::cin)  // fin de la entrada
        return false;
    priority_queue<int> libros;

    while (nlibros--) {
        std::cin >> aux;
        libros.push(aux);
    }
    int N = libros.size();
    for (int i = 0; i < N; i++) {
        if ((i + 1) % 3 == 0) { // libro en tercera posición
            ahorrado += libros.top();
            libros.pop();
        } else {
            libros.pop();
        }
    }
    std::cout << ahorrado << "\n";
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
