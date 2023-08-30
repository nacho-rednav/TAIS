#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <algorithm>

/*
* La solución consiste en implementar un algoritmo voraz cuya estrategia
* voraz es elegir las películas de menor a mayor hora de acabar y en caso de empate
* se elige la que empiece más tarde, porque ocupa menos tiempo del día. El test de factibilidad
* consistirá en que no se solape con una película ya elegida.
* 
* Demostración de corrección:
* Al comparar la solución del algoritmo con una solución óptima cualquiera:
* Llamamos xi (de solución voraz) e yj (de solución óptima) a los primeros elementos
* diferentes que encontramos entre las soluciones
* - Todo lo previo a xi e yi es igual en ambas soluciones
* - xi.fin <= yj.fin ya que en caso contrario el voraz hubiese elegido a yj antes que xi
* 
* - Si xi.fin == yi.fin es irrelevante que xi.ini != yi.ini ya que los elementos previos a
* xi e yi eran iguales por lo que el tiempo de comienzo no crearía solapamiento osea que podemos
* proponer cambio de yi por xi y que la solución siga siendo óptima
* - Si xi.fin < yi.ini el tiempo de comienzo vuelve a ser irrelevante por lo explicado en el caso
* anterior y puede proponerse cambio de xi por yi ya que xi termina antes, por lo que no solapará con
* nadie que no solapase con yi así que la solución sigue siendo óptima
*
* Podemos realizar estos cambios hasta que la solución voraz sea igual a una solución óptima cualquiera
*/

struct Peli{
	int ini, fin;
	Peli():ini(0), fin(0){}
	Peli(int i, int f):ini(i), fin(f){}

	bool operator<(const Peli& p)const {
		return fin < p.fin ||
			(fin == p.fin && ini > p.ini);
	}
};

int resuelve(const vector<Peli>& p) {
	int res = 1;
	int ulti = p[0].fin;
	//Vas cogiendo y tienes que mirar que la que eliges
	//no empiece antes de lo que la última que elegiste acaba
	for (int i = 1; i < p.size(); i++) {
		if (p[i].ini >= ulti + 10) {
			res++;
			ulti = p[i].fin;
		}
	}
	return res;
}

bool tratar_caso() {
	int N, h, m, d;
	int ini, fin;
	char c;
	vector<Peli> pelis;
	cin >> N;
	if (N == 0) return false;
	for (int i = 0; i < N; i++) {
		cin >> h >> c >> m >> d;
		ini = h * 60 + m;
		fin = ini + d;
		pelis.push_back({ ini, fin });
	}
	sort(pelis.begin(), pelis.end());
	cout << resuelve(pelis) << "\n";
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