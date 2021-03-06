#include <iostream>
#include <iomanip>
#include <fstream>
#include"PriorityQueue.h"

struct activity {
    int start;
    int end;
};

bool operator<(activity const& a, activity const& b) {
    return a.start < b.start;
}

int friends(PriorityQueue<activity, std::less<activity>> &_q) {

    int num_friends = 0;
    //auto it = _q.top(); // saco la primera tarea ya que siempre puedo hacer una
    PriorityQueue<int> end_of_activities;
    end_of_activities.push(_q.top().end);
    int n = _q.size() - 1;
    _q.pop();
    
    while (n--) {
        if (end_of_activities.top() > _q.top().start) // si la actividad en la que estoy acaba mas tarde que la actividad siguiente
            num_friends++;

        else
            end_of_activities.pop();
        end_of_activities.push(_q.top().end);
        _q.pop();
    }
    return num_friends;
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num_activities;
    std::cin >> num_activities;
    if (!num_activities)
        return false;

    PriorityQueue<activity, std::less<activity>> _q;

    int start, end;
    while (num_activities--) {
        std::cin >> start >> end;
        _q.push({ start,end });
    }

    std::cout << friends(_q) << "\n";

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
