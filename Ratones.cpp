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
#include <limits>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

using namespace std;


/*@ <answer>
 
 La solución consiste en realizar el algoritmo de Djikstra sobre el grafo inverso al que nos dan en el problema
 usando el vértice destino como origen.
 De esta forma obtenemos la distancia mínima del destino a cada vértice. Tras esto simplemente hay+que mirar en el
 vector dist qué vértices están a una distancia menor que el tiempo que nos dicen

 A = num aristas del grafo. V = número de vértices
 Coste = max(O(A log V), O(V)) que es el coste del algoritmo de Djikstra y de inicilizar la clase laberinto
 
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>


class Laberinto {
public:
    Laberinto(const DigrafoValorado<int>& g, int N, int destino, int tiempo) : ratones(0), pq(N), dist(N, INF) {//max(O(V), O(A log V))
        dijkstra(g, destino);
        for (int i = 0; i < N; i++) {
            if (i != destino && dist[i] <= tiempo) ratones++;
        }
    }

    int res() { return ratones; }

private:
    const int INF = numeric_limits<int>::max();
    int ratones;
    IndexPQ<int> pq;
    vector<int>dist;

    void relajar(AristaDirigida<int>& a, vector<int>& dist, IndexPQ<int>& pq) {
        int w = a.hasta();
        int v = a.desde();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }

    void dijkstra(const DigrafoValorado<int>& g, int origen) { //O(AlogV)
        dist[origen] = 0;
        pq.push(origen, 0);

        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a, dist, pq);
        }
    }
};



bool resuelveCaso() {
  
  // leemos la entrada
  int N, S, T, P, v, w, valor;
  cin >> N >> S >> T >> P;
  
  if (!cin)
    return false;

  // leer el resto del caso y resolverlo
  DigrafoValorado<int>g (N);

  for (int i = 0; i < P; i++) {
      cin >> v >> w >> valor;
      g.ponArista({ w - 1, v - 1, valor });
  }
  
  Laberinto l(g, N, S-1, T);
  cout << l.res() << "\n";
  
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
