/*
 * MUY IMPORTANTE: Solo se corregir�n los comentarios y el c�digo
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificaci�n fuera de esas etiquetas no ser� corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes hab�is hecho esta soluci�n:
  * Estudiante 1: V�ctor Ortego Mart�n TAIS72
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
    Sea n = n�mero de instrumentos, p = n�mero de partituras y c = n�mero de casos
    El coste total de la soluci�n estar� en O(c * max(n, (n-p)*logn)), ya que O(n) es el
    coste de leer los datos y O((p-n)logn) es el coste de la funci�n soluci�n

    Creamos un struct instrumento en el cual guardamos para cada tipo de instrumento el n�mero
    de m�sicos y el n�mero de partituras que se les va asignando a ese tipo de instrumento.
    Creamos una cola de prioridad de m�ximos en la que el m�s prioritario ser� aquel instrumento
    cuya aglomeraci�n de m�sicos, repartidos por partituras, sea mayor.
    Se realizan p-n iteraciones y en cada iteraci�n se saca al m�s prioritario de la cola, se le
    da otra partitura y se le vuelve a meter en la cola.
    El resultado es la aglomeraci�n del que es m�s prioritario tras terminar
    todas las iteraciones.

 @ </answer> */


 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo (despu�s de la marca)
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
//  Lo que se escriba dejado de esta l�nea ya no forma parte de la soluci�n.

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