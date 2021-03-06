#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 El ejercicio empieza leyendo los datos de los dos tipos de pilas en dos colas de prioridad ordenadas de mayor a menor.
 La cola A es para pilas de 9 y la cola B para pilas de 1,5

 La funcion volandoDrones toma las dos colas de prioridad y hace lo siguiente:
 
 El primer bucle while existe para sacar los drones a volar cada sabado comprobando que queden pilas en las colas(cajas).
 Dentro de este bucle se crean dos vectores auxiliares para almacenar la bateria restante de las pilas para cuando volvamos al club devolverlas.
 A su vez tenemos un contador horas para las horas totales de vuelo y un contador i para el numero de drones donde pusimos pilas.
 
 El segundo bucle while es el que se encarga de recargar los drones:
    Coge el primer dron y lo carga con las pilas con más bateria.
    Vuela el dron y almacena en los vectores auxiliares la pila que aun tiene bateria(si ambas pilas tenian la misma bateria no se mete ninguna).
    Se aumenta en 1 el contador de drones volados y se almacena la cantidad de horas que voló el dron.
    Esto se repite mientras queden pilas o mientas tengamos drones para cargar

 Una vez hecho esto, se muestra el total de horas voladas este sabado y se devuelven a la caja original las pilas que aun tienen bateria

 El coste de insertar en las colas de prioridad es del orden de O(A log A) y O(B log B) correspondientemente a cada cola.
 El coste de los dos bucles es O(N^2)

 La coste del poblema esta en O(N^2)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

void volandoDrones(priority_queue<int>A, priority_queue<int>B, int drones) {
    while (!A.empty() && !B.empty()) {

        int i = 0;
        int horas = 0;
        vector<int> restantesA;
        vector<int> restantesB;

        while (!A.empty() && !B.empty() && i < drones) {
            int pilaA = A.top();
            int pilaB = B.top();
            A.pop();
            B.pop();

            if (pilaA > pilaB) {
                restantesA.push_back(pilaA - pilaB);
            }
            else if (pilaB > pilaA) {
                restantesB.push_back(pilaB - pilaA);
            }
            i++;
            horas += min(pilaA, pilaB);
        }
        std::cout << horas << " ";
        for (int i = 0; i < restantesA.size(); i++) {
            A.push(restantesA[i]);
        }
        for (int i = 0; i < restantesB.size(); i++) {
            B.push(restantesB[i]);
        }
    }

}

bool resuelveCaso() {

    int drones, A, B, aux;
    std::cin >> drones >> A >> B;
    if (!std::cin)  // fin de la entrada
        return false;

    priority_queue<int> pilasA;
    priority_queue<int>pilasB;

    for (int i = 0; i < A; i++) {
        std::cin >> aux;
        pilasA.push(aux);
    }
    for (int i = 0; i < B; i++) {
        std::cin >> aux;
        pilasB.push(aux);
    }

    volandoDrones(pilasA, pilasB, drones);
    std::cout << "\n";
    
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
