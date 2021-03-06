#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#include "Matriz.h" // propios o los de las estructuras de datos de clase

struct festival {
    int grupos;
    int precio;
};

/*@ <answer>

 Resuelto mediante programacion dinamica. Maximizar el numero de grupos a los que ir

 resolver(i, p) = numero maximo de conciertos a los que se puede ir yendo al festival i con un presupuesto p

 resolver(i, p) = resolver (i-1, p) si p < festival[i].precio  (si el precio del festival es mas alto que mi presupuesto)
                  max(resolver(i-1, p), resolver(i-1, p-festival[i].precio) + festival[i].grupos)  maximo de grupos entre ir al festival i o no ir

 resolver(0, p) = 0 
 resolver(i, 0) = 0

 Primeramente está hecho con una matriz y posteriormente se mejorará el espacio a un vector(para practicar ambos metodos)

 Matriz de dimensiones 

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


int resolver(vector<festival> const &festivales, int presupuesto) {
    
    //Matriz<int> matrix(festivales.size() + 1, presupuesto + 1);
    vector<int> vector(presupuesto + 1, 0);
    //matrix[0][0] = 0;

    for (int i = 1; i < festivales.size(); i++) {
        for (int j = presupuesto; j >= festivales[i].precio; j--) {
                vector[j] = max(vector[j], vector[j - festivales[i].precio] + festivales[i].grupos);
        }
    }
    return vector[presupuesto];
}

bool resuelveCaso() {

    int presupuesto, nfestivales;
    std::cin >> presupuesto >> nfestivales;
    if (!std::cin)  // fin de la entrada
        return false;

    vector<festival> festivales(nfestivales + 1);
    int precio, grupos;
    for (int i = 1; i <= nfestivales; i++) {
        cin >> grupos >> precio;
        festivales[i] = { grupos,precio };
    }

    cout << resolver(festivales, presupuesto) << "\n";
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
