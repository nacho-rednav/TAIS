#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <iostream>


/*

Recurrencia:
	j representa la puntuación a obtener
	i representa el conjunto de las puntuaciones de 1 a i


	diana(0, j) = INF con j > 0
	diana(i, 0) = 0

	diana(i, j) = { diana(i-1, j) si punts[i] > j
				= { min(diana(i-1, j), diana(i, j - punts[i]) + 1)

*/

const int INF = 1000000000;


vector<int> resuelve(const vector<int>& punts, int P) {
	int n = punts.size();
	vector<int> v(P+1, INF);
	vector<int>sol;
	v[0] = 0;
	
	for (int i = 1; i < n; i++) {
		for (int j = punts[i]; j <= P; j = j+ 1) {
			v[j] = min(v[j], v[j - punts[i]] + 1);
		}
	}
	if (v[P] != INF) {
		int j = P;
		for (int i = n-1; i > 0; i--) {
			if (j - punts[i] >= 0 && v[j] == v[j - punts[i]] + 1) {
				sol.push_back(punts[i]);
				j -= punts[i];
				i++;
			}
		}
	}


	return sol;
}

bool tratar_caso() {
	int P, N, aux;
	cin >> P >> N;
	if (!cin)return false;
	vector<int> p(N + 1);
	for (int i = 1; i <= N; i++) {
		cin >> p[i];
	}

	vector<int> sol = resuelve(p, P);
	int n = (int)sol.size();

	if (n > 0) {
		cout << n << ":";
		for (int p : sol) {
			cout << " "; cout << p;
		}
	}
	else {
		cout << "Imposible";
	}
	cout << "\n";
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