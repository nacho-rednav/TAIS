#include <iostream>
#include <fstream>
using namespace std;
#include<vector>
#include <algorithm>

/*
Se ordenan edificios en orden creciente según su posición de inicio
La estrategia consiste en elegir el edificio que empieza antes de los
que quedan por elegir. Se considera que todos los edificios que estén dentro del
rango que ocupa ese edificio pueden usar un mismno pasadizo. Si encontramos
un edificio que termina antes que el elegido incialmente entonces el rango sólo puede
llegar hasta donde llegue ese edificio.
Cuando se encuentra un edificio que comienza fuera del rango se debe
comenzar un nuevo pasadizo
*/
/*
Dem:
Tenemos dos soluciones, X(voraz) e Y(optima)
Las soluciones se representan como una lista de conjuntos,
cada conjunto representa los edificios que usarán un mismo edificio

*/

struct Edificio {
	int ini, fin;

	Edificio() :ini(0), fin(0) {};
	Edificio(int i, int f) :ini(i), fin(f) {};

	bool operator<(const Edificio& e)const {
		return ini < e.ini ||
			(ini == e.ini && fin < e.fin);
	}
};

int resuelve(const vector<Edificio>& v) {
	int res = 1;
	int hasta = v[0].fin;

	for (int i = 1; i < v.size(); i++) {
		if (v[i].ini >= hasta) {
			res++;
			hasta = v[i].fin;
		}
		else if (v[i].fin < hasta) {
			hasta = v[i].fin;
		}
	}
	return res;
}

bool tratar_caso() { //O(N log N)
	int N, i, f;
	cin >> N;
	if (N == 0)return false;
	vector<Edificio> v;

	for (int j = 0; j < N; j++) {
		cin >> i >> f;
		v.push_back({ i, f });
	}
	sort(v.begin(), v.end()); //O(N log N)
	cout << resuelve(v) << "\n"; //O(N)
	return true;
}

int main() {
#ifndef DOMJUDGE
	std::ifstream in("sample.in");
	auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

	while (tratar_caso()) {}

#ifndef DOMJUDGE
	std::cin.rdbuf(cinbuf);
	// Descomentar si se trabaja en Windows
	// system("PAUSE");
#endif
	return 0;
}