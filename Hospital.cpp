#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct paciente {
	int gravedad;
	int llegada;
	string nombre;

	bool operator<(const paciente& p) const {
		return p.gravedad > gravedad ||
			(p.gravedad == gravedad && p.llegada < llegada);
	}
};

//N numero de eventos, M numero de pacientes
//Coste: O(N logM)
bool tratar_caso() {
	int n;
	string e;
	paciente p;
	priority_queue<paciente> hosp;
	cin >> n;
	if (n == 0) return false;

	for (int i = 0; i < n; i++) {//O(N)
		cin >> e;
		if (e == "I") {
			cin >> p.nombre >> p.gravedad;
			p.llegada = i;
			hosp.push(p); //O(log M)
		}
		else if (e == "A") {
			p = hosp.top();
			hosp.pop(); //O(log M)
			cout << p.nombre << "\n";
		}
	}
	cout << "---\n";

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