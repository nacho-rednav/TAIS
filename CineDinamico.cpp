#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <string>
#include <algorithm>
/*

pelis(i) = maximo de minutos que puedes estar viendo pelis teniendo
		   disponibles las pelis de la i a la n


pelis(i) = 0 si i > n
pelis(i) = max(pelis(i+1), duracion[i] + pelis(j)) si i < n
			j = indice primera peli que puede verse si eliges ver i

*/

struct Peli {
	int hora;
	int duracion;

	Peli():hora(0), duracion(0){}
	Peli(int h, int d):hora(h), duracion(d){}

	bool operator<(const Peli& p) const {
		return hora < p.hora;
	}
};

int INF = 1000000000;

int pelis(const vector<Peli>& v) {
	int n = v.size();
	vector<int> res(n+1, INF);
	
	res[n] = 0;
	res[n - 1] = v[n - 1].duracion;
	for (int i = n - 2; i >= 0; i--) {
		int o1 = res[i + 1];

		Peli p(v[i].hora + v[i].duracion + 10, 0);
		auto it = lower_bound(v.begin() + i, v.end(), p);
		int j = std::distance(v.begin(), it);
		int o2 = v[i].duracion + res[j];
		res[i] = max(o1, o2);
	}
	return res[0];
}

bool tratar_caso() {
	string hora;
	int n, h, min, dur;
	cin >> n;
	if (n == 0)return false;
	vector<Peli> v(n);
	for (int i = 0; i < n; i++) {
		cin >> hora >> dur;
		h = stoi(hora.substr(0, 2));
		min = stoi(hora.substr(3));
		v[i] = { 60 * h + min, dur };
	}

	sort(v.begin(), v.end());

	cout << pelis(v) << "\n";
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