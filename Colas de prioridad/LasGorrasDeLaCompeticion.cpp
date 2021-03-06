/*@ <answer>
 *
 * Nombre y Apellidos: Miguel robledo blanco
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <queue>
#include <vector>


 // propios o los de las estructuras de datos de clase

 /*@ <answer>

  Primeramente se ordenan los equipos de menor a mayor para minimizar el numero de gorras compradas.

  Si solo hay un equipo en la competición, se compran 0 gorras ya que no se juega ningun partido.
  En caso contrario, en cada vuelta del bucle se sacan los dos equipos con menos seguidores.
  Se suma al total de gorras la suma de sus seguidores, y se vuelve a meter en la cola esa misma suma.
  Esto se repite hasta que solo quede un valor en la cola(no se pueden jugar mas partidos)


  Siendo N el numero de equipos : 
  El coste de leer los datos de entrada es del orden de O(N log N)
  El coste de calcular el numero de gorras es del orden de O(N log N)
  Esto se debe a que las operaciones de push y pop en las colas de prioridad estan basadas en monticulos.
  Para cada elemento N, encontrar su posicion en la cola tiene coste del orden de O(log N)
  
  Esto resulta en que el problema tiene coste O(N log N)

  @ </answer> */


  // ================================================================
  // Escribe el código completo de tu solución aquí debajo
  // ================================================================
  //@ <answer>

int64_t solucion(std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> cola) {
    int64_t equipo1, equipo2, gorras = 0;
    while (cola.size() > 1) {
        equipo1 = cola.top();
        cola.pop();
        equipo2 = cola.top();
        cola.pop();

        cola.push(equipo1 + equipo2);
        gorras += equipo1 + equipo2;
    }
    return gorras;
}
bool resuelveCaso() {

    int64_t equipos, gorras = 0, aux;
    std::cin >> equipos;

    if (equipos == 0)
        return false;

    std::priority_queue<int64_t,std::vector<int64_t>, std::greater<int64_t>> seguidores;

    while (equipos--) { // leer los seguidores
        std::cin >> aux;
        seguidores.push(aux);
    }

    if (seguidores.size() > 1) { // se juega algun partido
        gorras += solucion(seguidores);

    } else {
        gorras = 0;
    }
    std::cout << gorras << "\n";

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

