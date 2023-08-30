#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

/*
	luces(i, j) = minimo coste que habra que pagar para cubrir una potencia j
				  con las bombillas de la 1 a la i

	luces(i, j) = { luces(i-1, j) si potencia[i] > j
				  { min(luces(i-1, j), luces(i, j - potencia[i]) + coste[i])
	luces(0, j) = INF j > 0
	luces(i, 0) = 0

*/

const int INF = 2000000000;

struct Bombilla {
	int potencia;
	int coste;
};

void resolver(const vector<Bombilla>& b, int N, int PX, int PI) {
	vector<int>res(PX+1, INF);
	res[0] = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= PX; j++) {
			if (b[i].potencia <= j) {
				res[j] = min(res[j], res[j - b[i].potencia] + b[i].coste);
			}
		}
	}

	if (PX < PI) {
		cout << "IMPOSIBLE\n";
	}
	else {
		int mini = res[PI], j = PI;
		for (int i = PI + 1; i <= PX; i++) {
			if (res[i] < mini) {
				mini = res[i];
				j = i;
			}
		}
		if (mini == INF) cout << "IMPOSIBLE\n";
		else cout << mini << " " << j << "\n";
		/*else {				RECONSTRUCION
			int bombilla = N;
			vector<int> bombs;
			while (j > 0 && bombilla > 0) {
				if (b[bombilla].potencia <= j &&
					res[j] == res[j - b[bombilla].potencia] + b[bombilla].coste) {
					j -= b[bombilla].potencia;
					bombs.push_back(b[bombilla].potencia);
				}
				else {
					bombilla--;
				}
			}

			cout << mini << "\n";
			for (int i : bombs) cout << i << " ";
			cout << "\n";
		}*/
	}
}

bool tratar_caso() {
	int N, PX, PI;
	cin >> N >> PX >> PI;
	if (!cin) return false;
	vector<Bombilla> v(N+1);

	for (int i = 1; i <= N; i++) {
		cin >> v[i].potencia;
	}
	for (int i = 1; i <= N; i++) {
		cin >> v[i].coste;
	}

	resolver(v, N, PX, PI);
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