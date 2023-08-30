#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

/*
corte(i, j) = minimo esfuerzo para cortar una tabla que va del corte i al j

corte(i, j) = 0 si i >= j + 1
corte(i, j) = min (i < k < j) { corte(i,k) + corte(k, j) + (j-i)*2
*/

const int INF = 100000000000;

int corte(const vector<int>& v) {

	int n = v.size();
	vector<vector<int>> res(n, vector<int>(n, 0));

	for (int i = n - 2; i >= 0; i--)
		for (int j = i + 2; j < n; j++) {
			res[i][j] = INF;
			for (int k = i+1; k < j; k++) {
				int temp = res[i][k] + res[k][j] + 2 * (v[j] - v[i]);
				if (temp < res[i][j])
					res[i][j] = temp;
			}
		}
	return res[0][n - 1];
}

bool tratar_caso() {
	int L, C;
	cin >> L >> C;
	if (L + C == 0) return false;
	vector<int>tabla(C + 2);
	tabla[0] = 0;
	tabla[C + 1] = L;
	for (int i = 1; i <= C; i++) cin >> tabla[i];

	cout << corte(tabla) << "\n";

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