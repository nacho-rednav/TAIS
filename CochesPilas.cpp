#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <algorithm>

/*
Estrategia voraz: 
Emparejar la pila más pequeña disponible con la más grande
Son admisibles si su suma supera o iguala el mínimo al que llegar

Dem:
Solucion optima Y y solucion voraz X, c
Las respuestas son pares (ai, bi)voraz (cj, dj)optima

Colocamos las respuestas de la siguiente forma:
El primer elemento del par es el mayor de los dos en todos los pares
Se colocan en orden decreciente de elemento mayor
Al encontrar una diferencia:
- Si ai != ci -> ci < ai por como elige la voraz y ai no se usa en Y
  porque si no hubiese aparecido en las respuestas anteriores de Y pero no lo hizo.
  Podemos cambiar ci por ai

	Si bi != dj -> Si bi no se usa puedo hacer el cambio y quedarme el par (ai, bi) en Y
				   Si bi sí se usa puedo hacer el cambio, quedarme con el par(ai, bi) en Y y como dj > bi 
				   (por como elige la solución voraz las soluciones) la pareja anterior de bi segura siendo válida con dj

*/


int resuelve(const vector<int>& p, int V) {
	int res = 0;
	int i = 0, j = p.size() - 1;

	while (i < j) {
		if (p[i] + p[j] >= V) {
			res++; i++; j--;
		}
		else {
			i++;
		}
	}
	return res;
}

void tratar_caso() {
	int N, V, aux;
	vector<int>pilas;
	cin >> N >> V;
	for (int i = 0; i < N; i++) {
		cin >> aux; pilas.push_back(aux);
	}
	sort(pilas.begin(), pilas.end());
	cout << resuelve(pilas, V) << "\n";
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	int i = 0, n;
	cin >> n;
	while (i < n) { i++; tratar_caso(); }

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}