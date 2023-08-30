#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

int resuelve(const vector<int>& m, int L) {
	int parches = 1;
	int ini = m[0];

	for (int i = 1; i < m.size(); i++) {
		if (m[i] - ini > L) {
			parches++;
			ini = m[i];
		}
	}


	return parches;
}

bool tratar_caso() {
	int N, L, aux;
	vector<int> manguera;
	cin >> N >> L;
	if (!cin) return false;
	for (int i = 0; i < N; i++) {
		cin >> aux; manguera.push_back(aux);
	}

	cout << resuelve(manguera, L) << "\n";

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