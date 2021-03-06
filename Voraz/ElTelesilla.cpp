#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Se utiliza un algoritmo voraz ordenando los elementos de menor a mayor(se puede resolver de igual forma ordenando de mayor a menor)
 Funcion Objetivo : minimizar el numero de sillas dobles
 Conjunto de candidatos: Pesos de las personas en el fichero txt
 Test de factibilidad: Persona mas delgada + persona mas gorda <= Peso maximo de la silla
 Funcion de seleccion: Dos indices flaco y gordo, al comienzo y al final del vector indican cuales son las dos siguientes personas a tratar

 Cuando se compruebe el valor de los pesos en los dos indices siempre se va a disminuir el indice que apunta a la persona mas gorda(si entran los dos,
 se disminuye gordo y el flaco, si solo sube el mas gordo, tambien se disminuye), por esta razon "gordo--" esta fuera del if, solamente cuando las 
 dos personas puedan subirse a la silla se disminuye primeramente "flaco" y lugo "gordo"

 El primer if existe para cuando tenemos impar personas, en cuyo caso se suma siempre una silla y se modifica cualquiera de los indices para salir
 del bucle.

 El coste de la solucion en el caso peor es O(N) siendo N el numero de personas

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int sillas(std::vector<int> peso, int maxPeso) {
    int flaco = 0, gordo = peso.size() - 1;
    int total = 0;

    while (flaco <= gordo) {
        if (flaco == gordo) {
            total++;
            flaco++;
        } else {
            if (peso[flaco] + peso[gordo] <= maxPeso) {
                flaco++;
            }
            gordo--;
            total++;
        }
    }
    return total;
}

bool resuelveCaso() {

    int maxPeso, npersonas;
    std::cin >> maxPeso >> npersonas;

    if (!std::cin)  // fin de la entrada
        return false;

    std::vector<int> personas(npersonas);
    for (int i = 0; i < npersonas; i++) {
        std::cin >> personas[i];
    }

    std::sort(personas.begin(), personas.end());

    std::cout << sillas(personas, maxPeso) << "\n";
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
