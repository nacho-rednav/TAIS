#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <queue>

struct Actividad {
	int inicio;
	int fin;

	bool operator<(const Actividad& a) const{
		return a.inicio < inicio;
	}
};


bool tratar_caso() {
	int N, in, f;
	Actividad aux;
	priority_queue<Actividad> acts;
	priority_queue<int, vector<int>, greater<int>> companeros;

	cin >> N;
	if (N == 0) return false;
	for (int i = 0; i < N; i++) {
		cin >> in >> f;
		acts.push({ in, f });
	}

	companeros.push(acts.top().fin);
	acts.pop();
	while (!acts.empty()) {
		aux = acts.top(); acts.pop();
		if (aux.inicio >= companeros.top()) {
			companeros.pop();
		}
		companeros.push(aux.fin);
	}

	cout << companeros.size()-1 << "\n";

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