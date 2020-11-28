// Nombre del alumno .....
// Usuario del Juez ......


#include <iostream>
#include <iomanip>
#include <fstream>
#include"bintree_eda.h"


struct tSol {
    int minimo;
    int maximo;
    bool ok;
    int altura;
};

tSol bin_busqueda(bintree<int> tree, tSol sol) {
    if (!tree.empty()) {
        if (tree.left().empty() && tree.right().empty()) { // nodo hijo
            sol.maximo = tree.root();
            sol.minimo = tree.root();
            sol.altura = 1;
        }
        else if (!tree.left().empty() && tree.right().empty()) { // solo hijo izdo
            sol = bin_busqueda(tree.left(), sol);

            if (sol.ok && tree.root() > sol.maximo && sol.altura<2) {
                sol.maximo = tree.root();
                sol.altura++;

                if (tree.root() < sol.minimo) sol.minimo = tree.root();
            }
            else sol.ok = false;
        }
        else if (tree.left().empty() && !tree.right().empty()) { // solo hijo derecho
            sol = bin_busqueda(tree.right(), sol);

            if (sol.ok && tree.root() < sol.minimo && sol.altura<2) {
                sol.minimo = tree.root();
                sol.altura++;

                if (tree.root() > sol.maximo) sol.maximo = tree.root();
            }
            else sol.ok = false;
        }
        else {
            tSol leftTree = bin_busqueda(tree.left(), sol);
            tSol rightTree = bin_busqueda(tree.right(), sol);
            sol.altura = std::max(leftTree.altura, rightTree.altura) + 1;
            int diferencia = abs(leftTree.altura-rightTree.altura);
            if (leftTree.ok && rightTree.ok && tree.root() > leftTree.maximo && tree.root() < rightTree.minimo && diferencia<2)
            {
                if (leftTree.maximo > rightTree.maximo)
                    sol.maximo = leftTree.maximo;
                else
                    sol.maximo = rightTree.maximo;

                if (leftTree.minimo < rightTree.minimo)
                    sol.minimo = leftTree.minimo;
                else
                    sol.minimo = rightTree.minimo;
            }
            else sol.ok = false;
        }
    }

    return sol;
}


// Resuelve un caso de prueba, leyendo de la entrada la
// configuración, y escribiendo la respuesta
void resuelveCaso() {
    // leer los datos de la entrada
    bintree<int> arbol;
    
    arbol = leerArbol(-1);

    tSol sol = bin_busqueda(arbol, {0,0,true,0});

    if (sol.ok)
        std::cout << "SI\n";
    else
        std::cout << "NO\n";

}

int main() {
    // Para la entrada por fichero.
    // Comentar para acepta el reto
#ifndef DOMJUDGE
    std::ifstream in("datos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf()); //save old buf and redirect std::cin to casos.txt
#endif 


    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();


    // Para restablecer entrada. Comentar para acepta el reto
#ifndef DOMJUDGE // para dejar todo como estaba al principio
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif

    return 0;
}