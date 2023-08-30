/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: Víctor Ortego Martín TAIS72
  * Estudiante 2: Ignacio Redondo Navarro TAIS85
  * 
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;


/*@ <answer>
    Sea n = número de instrumentos, p = número de partituras y c = número de casos
    El coste total de la solución estará en O(c * max(n, (n-p)*logn)), ya que O(n) es el
    coste de leer los datos y O((p-n)logn) es el coste de la función solución

    Creamos un struct instrumento en el cual guardamos para cada tipo de instrumento el número
    de músicos y el número de partituras que se les va asignando a ese tipo de instrumento.
    Creamos una cola de prioridad de máximos en la que el más prioritario será aquel instrumento
    cuya aglomeración de músicos, repartidos por partituras, sea mayor.
    Se realizan p-n iteraciones y en cada iteración se saca al más prioritario de la cola, se le
    da otra partitura y se le vuelve a meter en la cola.
    El resultado es la aglomeración del que es más prioritario tras terminar
    todas las iteraciones.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

struct instrumento {
    int musicos;
    int partituras;

    int maxGrupo() const{
        int res = musicos / partituras;
        if (musicos % partituras != 0) {
            res += 1;
        }
        if (partituras >= musicos) {
            res = 1;
        }
        if (partituras == 1) {
            res = musicos;
        }
        return res;
    }

    bool operator<(const instrumento& i) const {
        return i.maxGrupo() > maxGrupo();
    }
};

int solucion(int p, int n, priority_queue<instrumento>& grupos) { //O((p-n)logn)
    int sobra = p - n;
    instrumento max;

    while (sobra > 0) { //O(p-n)
        max = grupos.top();
        grupos.pop();//O(logn)
        max.partituras++;
        grupos.push(max);//O(logn)
        sobra--;
    }

    return grupos.top().maxGrupo();
}

bool resuelveCaso() {

    // leemos la entrada
    int P, N;
    cin >> P >> N;
    instrumento aux;
    priority_queue<instrumento> grupos;

    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    for (int i = 0; i < N; i++) { //O(n)
        cin >> aux.musicos;
        aux.partituras = 1;
        grupos.push(aux);
    }

    cout << solucion(P, N, grupos) << "\n"; //O((p-n)logn)

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

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}