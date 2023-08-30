/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

/*@ <answer>
 *
 * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
 * Estudiante 1: IGNACIO REDONDO NAVARRO TAIS85
 * Estudiante 2: VICTOR ORTEGO MARTIN TAIS72
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <limits>
using namespace std;


/*@ <answer>
 Coste: //O(NlogN) siendo N el número de resultados de partido por el coste de ordenar, el coste del voraz es //O(N)
 Para alcanzar la solución se ordena el vector de puntos de rivales
 de menor a mayor y el de puntos propios obtenidos de mayor a menor.
 Una vez ordenados así se van seleccionando en orden el elemento del
 vector de propios y el del vector de rivales y guardamos la diferencia
 hasta llegar a un elemento del vector de rivales que es mayor o igual que el 
 del vector de propios.
 Osea que los candidatos son cada una de los puntuaciones propias que se asginan a una
 puntuacion rival
 El candidato es factible si es > 0
 La estrategia voraz consiste en restar el máximo pi sin elegir con el mínimo ri sin elegir
 
 
 Tenemos una solución X (voraz) y una solución Y (óptima cualquiera)
 Se ordenan las puntuaciones rivales de menor a mayor y se les asginan las puntuaciones propias.
 Al encontrar una diferencia entre un xi y un yi asignados a un ri siempre habrá un yj = xi asignado a un rj en algún punto de la solución óptima
 Siempre se va a cumplir que xi > yi, porque si no el voraz la hubiese elegido para ese ri
 Posibilidades de la diferencia:
 ) xi <= ri -> Sabemos que yi tampoco gana porque entonces el voraz lo hubiese elegido por lo que en este cambio ambos siguen perdiendo ya que rj > ri
               por lo que tanto xi como yi pierden contra ambos, el cambio de yi por xi no afecta

 ) xi > ri
    &&   yi > rj ->  Como ri < rj y yi < yj sabemos (ri - yi) < (ri - yj) y (rj - yi) < (rj - yj) entonces el cambio (ri - yj) (rj - yi)
                      nos aporta menos en rj - yi pero nos aporta más en ri - yj, por lo que la solución no empeora
    &&    yi <= rj -> El cambio haría que yi siguiese perdiendo contra rj`pero ahora yj ganaría contra ri. Esto no puede darse porque mejoraría a Y, que es óptima
 
 SIN ACABAR
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

int maximizar(vector<int>& rivales, vector<int>& propios) {
    int puntosMax = 0, i = 0, j = 0;
    sort(rivales.begin(), rivales.end(), less<int>());
    sort(propios.begin(), propios.end(), greater<int>());

    while (i < rivales.size() && j < propios.size() && rivales[i] < propios[j]) {
        puntosMax += propios[j] - rivales[i];
        i++; j++;
    }

    return puntosMax;
}

bool resuelveCaso() {
  
  int N, aux;
  cin >> N;  // número de partidos
    
  if (N == 0) 
    return false;

  // leer el resto del caso y resolverlo
  
  vector<int> rivales;
  vector<int> propios;
  
  for (int i = 0; i < N; i++) {
      cin >> aux;
      rivales.push_back(aux);
  }
  for (int i = 0; i < N; i++) {
      cin >> aux;
      propios.push_back(aux);
  }
  
  cout << maximizar(rivales, propios) << "\n";

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
