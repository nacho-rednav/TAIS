/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

/*@ <answer>
 *
 * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
 * Usuario: TAIS72
 * Estudiante 1: VICTOR ORTEGO MARTIN
 * Estudiante 2: NACHO REDONDO NAVARRO
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;


/*@ <answer>
 
 La solucióm consiste en utilizar una cola de prioridad para que cada nuevo cliente acceda siempre
 a la cola del súper en la cual los clientes ya habrían terminado su turno. Cuando se acaba el número de clientes
 la cola que sea más prioritaria dentro de la cola de prioridad será aquella en la que, en total, los clientes tardan menos
 y por tanto a la que tiene que ir el enamorado
 
 C = num clientes, N = num cajas, NU = número de casos
 La función buscaCaja tiene un coste de O(ClogC)
 La función resuelveCaso tiene un coste de O(max(N, ClogC))
 El coste de la solución estará acotado por O(NU * max(N, ClogC))

 @ </answer> */


// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

struct cola {
    int segs;
    int n;

    cola(int nu) {
        segs = 0;
        n = nu;
    }

    bool operator<(const cola& c) const {
        return c.segs < segs || (c.segs == segs && c.n < n);
    }
};

int buscaCaja(priority_queue<cola>& colas, int C) { //O(ClogC)
    cola c(1);
    int t;
    for (int i = 0; i < C; i++) { //O(C)
        cin >> t;
        c = colas.top(); colas.pop(); //O(log C)
        c.segs += t;
        colas.push(c);// O(log C)
    }

    return colas.top().n;
}

bool resuelveCaso() {
  
  // leemos la entrada
  int N, C;
  priority_queue<cola> colas;
  cin >> N >> C;
  if (N == 0 && C == 0)
    return false;
  
  // leer el resto del caso y resolverlo
  for (int i = 1; i <= N; i++) {
      colas.push( { i }); //O(N)
  }
        
  cout << buscaCaja(colas, C) << "\n";
  
  
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
