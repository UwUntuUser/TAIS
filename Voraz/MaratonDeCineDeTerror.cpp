#include <iostream>
#include <iomanip>
#include <fstream>
#include"PriorityQueue.h"

struct hour {
    int h;
    int m;
};
struct movie {
    hour start;
    hour end;
};

bool operator <(hour const& a, hour const& b) {
    if (a.h == b.h) 
        return a.m < b.m;
    else 
        return a.h < b.h;
}
bool operator <=(hour const& a, hour const& b) {
   if (a.h == b.h) {
        if (a.m == b.m) 
            return true;
        else 
            return a.m < b.m;
   }
    else 
        return a.h < b.h;
}

bool operator <(movie const& a, movie const& b) { // comparator para la cola
    return a.end < b.end;
}
void addTime(hour& h, int min) {
    h.m += min;
    while (h.m >= 60) {
        h.h++;
        h.m -= 60;
    }
}
int movies(PriorityQueue<movie> &q) {
    int sol = 1;
    hour end = q.top().end;
    q.pop();
    int tam = q.size();
    while(tam--) {
        if (end <= q.top().start) {
            sol++;
            end = q.top().end;
        }
        q.pop();
    }
    return sol;
    
}
// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada
    int num_movies;
    std::cin >> num_movies;
    if (num_movies == 0)
        return false;

    PriorityQueue<movie> q;
    movie m;
    int duration;
    char trash;
    hour h;
    while (num_movies--) {
        std::cin >> h.h >> trash >> h.m >> duration;
        m.start = h;
        addTime(h, duration + 10);
        m.end = h;
        q.push(m);
    }

    std::cout << movies(q) << "\n";


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
