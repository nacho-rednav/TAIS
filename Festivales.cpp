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
using namespace std;


/*@ <answer>

 El problema se resuelve mediante programación dinánimca teniendo un
 coste en tiempo de O(N * P), siendo N = número de festivales y P = presupuesto.
 El espacio adicional que se utiliza es O(P), ya que por programación ascendente
 podemos resolver el programa utilizando solamente un vector.
 Se utiliza la siguiente recursión:

 numeroMax(i, j) = máximo número de grupos que pueden verse yendo a los festivales del 1 al i con un presupuesto j

    numeroMax(0,j) = 0 j > 0
    numeroMax(i,0) = 0
    numeroMax(i,j) = numeroMax(i - 1, j) si festivales[i].precio > j
                   = max(numeroMax(i - 1, j), numeroMax(i - 1, j - festivales[i].precio) + festivales[i].grupos) si festivales[i].precio <= j

numeroMax(0, j) = 0 si j > 0 porque si tenemos un conjunto vacío de festivales no podremos ver ningún concierto
numeroMax(i, 0) = 0 ya que sin no tenemos presupuesto no podremos ir a ningún festival

numeroMax(i, j) = numeroMax(i -1 , j) si festivales[i].precio > j ya que este caso representa el caso en el que el festival i se te sale de presupuesto
                                                                  por lo que no seleccionamos este festival. Por eso su resultado será el mismo que el que aporta
                                                                  la recursión sin ir al festival i, osea, los festivales del 1 al i-1
numeroMax(i, j) = max(numeroMax(i - 1, j), numeroMax(i - 1, j - festivales[i].precio) + festivales[i].grupos) si festivales[i].precio <= j
Ya que este es el caso en el que sí podemos elegir el festival i. Entonces la recursión debe devolver la mejor opción entre
no coger este festival (numeroMax(i -1 , j)) y sí cogerlo (numeroMax(i - 1, j - festivales[i].precio) + festivales[i].grupos)
numeroMax(i - 1, j - festivales[i].precio) + festivales[i].grupos representa elegir este festival porque descontamos del presupuesto
al hacer j - festivales[i].precio y a la solución le suma los grupos de ir a este festival festivales[i].grupos

Podemos utilizar solamente un vector ya que la para calcular la fila i sólo necesitamos la fila i-1
Como necesitamos acceder a la posición j - festivales[i].precio de la fila i-1 el vector se rellena de
derecha a izquierda
  
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>

/*
    

*/

struct Festival {
    int grupos;
    int precio;

};

int numeroMaxGrupos(int precioMax, vector<Festival> &festivales) {

    vector<int> tabla(precioMax + 1, 0);
    
    for (int i = 1; i < festivales.size(); i++) {
        for (int j = precioMax; j >= festivales[i].precio; j--) {
            tabla[j] = max(tabla[j], tabla[j - festivales[i].precio] + festivales[i].grupos);
        }
    }

    return tabla[precioMax];
}

bool resuelveCaso() {
  
  int P, N, nG, nP;
  cin >> P >> N;  // presupuesto y número de festivales
    
  if (!cin) 
    return false;

  // leer el resto del caso y resolverlo
  vector<Festival> festivales(N + 1);

  for (int i = 1; i <= N; i++) {
      cin >> nG >> nP;
      festivales[i] = { nG, nP };
  }
  
  cout << numeroMaxGrupos(P, festivales) << "\n";
  
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
