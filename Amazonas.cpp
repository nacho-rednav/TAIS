/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: VICTOR ORTEGO MARTIN TAIS72
  * Estudiante 2: IGNACIO REDONDO NAVARRO TAIS85
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;


//  IMPORTANTE: NO se admiten soluciones basadas en el algoritmo (y recurrencia)
//  de Floyd. Hay que pensar una recurrencia específica para este problema
//  que intente sacar partido de que el río solamente se puede recorrer en un
//  sentido.


/*@ <answer>

 viaje(i, j) = coste minimo de hacer el viaje desde i hasta j

 viaje(i, j) = 0 si i >= j
 viaje(i, j) = min(i < k <= j) { viaje(i, k) + viaje(k, j) } si i < j

 La solucion es un algoritmo de Floyd acortado ya que podemos
 ahorrarnos el trabajo de calcular toda distancia entre dos nodos (poblados)
 si ese nodo se encuentra antes en el rio, es decir, su indic en la matriz de adyacencia es menor.
 Pero para los poblados que estan despues se realiza un algoritmo de Floyd

 N = numero de poblados
 Coste: Tiempo(N3) aunque ahorremos trabajo sigue estando acotado por N al cuño
        Espacio(N2) por la matriz res de tamaño N*N

 @ </answer> */

 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>


bool resuelveCaso() {

    // leemos la entrada
    int N;
    cin >> N;

    if (!cin)
        return false;

    // leemos los alquileres
    vector<vector<int>> alquiler(N, vector<int>(N, 0));
    vector<vector<int>> res(N, vector<int>(N, 0));
    for (int i = 0; i < N - 1; ++i) {
        for (int j = i + 1; j < N; ++j) {
            cin >> alquiler[i][j];
            res[i][j] = alquiler[i][j];
        }
    }


    // resolver el caso
    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            for (int k = i + 1; k <= j; k++) {
                int temp = res[i][k] + res[k][j];
                if (temp < res[i][j])
                    res[i][j] = temp;
            }
        }
    }

    for (int i = 0; i < N; i++) {
        for (int j = i + 1; j < N; j++) {
            cout << res[i][j] << " ";
        }
        cout << "\n";
    }

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    // system("PAUSE");
#endif
    return 0;
}