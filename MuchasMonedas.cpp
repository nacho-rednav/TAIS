#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

/*
	monedas(i, j) = num mínimo de monedas necesarias para pagar cantidad j con las monedas
					desde 1 hasta i

	monedas(0, j) = INF j > 0
	monedas(i, 0) = 0

	monedas(i, j) = min { 0<=c<=disp[i], c*valor[i] <= j} ( monedas(i-1, j - c*valor[i]) + c)
*/

const int INF = 1000000000;

struct Moneda {
	int valor;
	int cantidad;
	Moneda():valor(0), cantidad(0){}
};

int resolver(const vector<Moneda>& m, int N, int val) {
	vector<vector<int>> res(N+1, vector<int>(val, INF));
	int temp, c;

	for (int i = 0; i < N; i++)res[i][0] = 0;

	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < val; j++) {
			c = 0;
			while (c <= m[i].cantidad && j >= c * m[i].valor) {
				temp = res[i - 1][j - c * m[i].valor] + c;
				if (temp < res[i][j])res[i][j] = temp;
				c++;
			}
		}
	}
	return res[N][val - 1];
}

bool tratar_caso() {
	int N, val;
	cin >> N;
	if (!cin) return false;
	vector<Moneda>v(N+1);
	for (int i = 1; i <= N; i++) {
		cin >> v[i].valor;
	}
	for (int i = 1; i <= N; i++) {
		cin >> v[i].cantidad;
	}
	cin >> val;

	int r = resolver(v, N, val + 1);
	if (r == INF) cout << "NO";
	else cout << "SI " << r;
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