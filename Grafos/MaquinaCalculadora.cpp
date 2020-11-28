// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include<queue>


class calculator{

private:

    std::queue<int>q;
    int max = 10000;
    int inf = 1000000000;
    int steps;

    int bfs(int start, int end) {

        if (start == end) return 0;

        std::vector<int>distance(max, inf);
        distance[start] = 0;
        q.push(start);

        while (!q.empty()) {
            auto it = q.front();
            q.pop();
            for (int i = 1; i <= 3; i++) {
                int a = ady(it, i);
                if (distance[a] == inf) // not visited
                {
                    distance[a] = distance[it] + 1;
                    if (a == end)
                        return distance[a];
                    else
                        q.push(a);
                }
            }
        }
    }

    int ady(int start, int op) {
        switch (op)
        {
        case 1: return (start + 1) % max;
        case 2: return (start * 2) % max;
        case 3: return (start / 3) % max;
        }
    }
public :
    
    calculator(int start, int end){
    
        steps =  bfs(start, end);
    };

    int num_steps(int end) {
        return steps;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int start, end;
    std::cin >> start >> end;

    if (!std::cin)
        return false;

    calculator c(start, end);
    std::cout << c.num_steps(end) << "\n";


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