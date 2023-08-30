#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <algorithm>

int resuelve(const vector<int>& e, const vector<int>& d) {
	int res = 0, indE = 0;

	for (int indD = 0; indD < d.size(); indD++) {
		if (e[indE] <= d[indD]) {
			res++;
			indE++;
		}
	}
	return res;
}

bool tratar_caso() {
	int N, aux;
	vector<int> enemigos;
	vector<int> defensa;
	cin >> N;
	if (!cin)return false;
	for (int i = 0; i < N; i++) {
		cin >> aux; enemigos.push_back(aux);
	}
	for (int i = 0; i < N; i++) {
		cin >> aux; defensa.push_back(aux);
	}
	sort(enemigos.begin(), enemigos.end());
	sort(defensa.begin(), defensa.end());

	cout << resuelve(enemigos, defensa) << "\n";
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