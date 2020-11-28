// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include<queue>

class tablero {

private:

    std::vector<bool> visitado;
    std::vector<int> distancia;
    std::vector<int> anteriores;
    int tamanio;

public:

    tablero(int t, int dado, std::vector<int> const& v) : tamanio(t), visitado(v.size()), distancia(v.size()), anteriores(v.size()) {
        std::queue<int> _q;
        visitado[1]=true;
        distancia[1] = 0;

        _q.push(1);
        // vamos a ir calculando la distancia minima desde 1 hasta el resto de casillas del tablero
        while (!_q.empty()) {
            int node = _q.front();
            _q.pop();

            for (int i = 1; i <= dado && node < t * t + 1; i++) { // para movernos en funcion de las tiradas del dado
                int new_node = node + i;
                if (new_node > t * t) return; // si por algun casual nos hemos salido del tablero al calcular la nueva tirada
                if (v[new_node] != 0) {// si existen atajos desde la posicion en la que estoy
                    new_node = v[new_node]; // cogemos el atajo
                }
                if (!visitado[new_node]) {  
                    visitado[new_node] = true;
                    distancia[new_node] = distancia[node] + 1;
                    anteriores[new_node] = node; // añadido por mi para ver el camino
                    _q.push(new_node);
                }
            }


        }

    }


    int sol() {
        return distancia[tamanio * tamanio];
    }

    std::vector<int> camino() {
        std::vector<int> v;
        for (int i = 100; i > 0; i = anteriores[i])
            v.push_back(i);
        return v;
    }
};

// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
bool resuelveCaso() {
    // leer los datos de la entrada

    int tab, dado, num_serpientes, num_escaleras;
    std::cin >> tab >> dado >> num_serpientes >> num_escaleras;

    if (tab == 0 && dado == 0 && num_escaleras == 0 && num_serpientes == 0)
        return false;

    std::vector<int> atajos(tab * tab + 1, 0);
    int comienzo, fin;
    for (int i = 0; i < num_escaleras + num_serpientes; i++) {

        std::cin>>comienzo >> fin;
        atajos[comienzo] = fin;
    }

    tablero t(tab, dado, atajos);

    std::cout << t.sol() << "\n";
    for (int node : t.camino())
        std::cout << node << " ";




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
