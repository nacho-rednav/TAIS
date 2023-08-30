#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <queue>

struct Bateria {
	int id;
	int carga;
	int tiempo;

	const bool operator<(const Bateria& b) const {
		return tiempo > b.tiempo ||
			(tiempo == b.tiempo && id > b.id);
	}
};

bool tratar_caso() {
	queue<Bateria> repuesto;
	priority_queue<Bateria> base;
	int B, R, Z, T, aux;
	cin >> B;
	if (!cin) return false;
	for (int i = 1; i <= B; i++) {
		cin >> aux;
		base.push({ i, aux, aux });
	}
	cin >> R;
	for (int i = 1; i <= R; i++) {
		cin >> aux;
		repuesto.push({ B + i, aux, aux });
	}
	cin >> Z >> T;

	while (!base.empty() && base.top().tiempo <= T) {
		Bateria aux = base.top();
		base.pop();
		aux.carga -= Z;
		if (aux.carga > 0) {
			aux.tiempo += aux.carga;
			base.push(aux);
		}
		else {
			if (!repuesto.empty()) {
				int t = aux.tiempo;
				aux = repuesto.front();
				repuesto.pop();
				aux.tiempo += t;
				base.push(aux);
			}
		}
	}
	if (base.empty()) {
		cout << "ABANDONEN INMEDIATAMENTE LA BASE\n";
	}
	else {
		if (base.size() < B) {
			cout << "FALLO EN EL SISTEMA\n";
		}
		else {
			cout << "CORRECTO\n";
		}
		while (!base.empty()) {
			cout << base.top().id << " " << base.top().tiempo << "\n";
			base.pop();
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