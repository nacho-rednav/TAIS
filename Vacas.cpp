#include <iostream>
#include <fstream>
using namespace std;
#include <vector>

/*
come(i, j) = max puede comer teninedo i, j como extremos y empezando ella a comer

come(i, j) = { max(cubos[i] + come(x, y),
					cubos[j] + come(x', y'))
			(x, y) = (i-1, j-1) si cubos[i-1] < cubos[j] o = (i-2, j) otro caso
			(x', y') => análogo a lo de arriba

come(i, i) = cubos[i]
come(i, j) = 0 si i > j
*/

int come(vector<vector<int>> & res, const vector<int>& cubos,const int i,const int j) {
	int op1 = 0, op2 = 0, x = 0, y = 0;
	if (res[i][j] != -1) return res[i][j];

	if (i == j) res[i][j] = cubos[i];
	else if (i > j) res[i][j] = 0;
	else {
		if (cubos[i + 1] > cubos[j]) {
			x = i + 2; y = j;
		}
		else {
			x = i + 1; y = j - 1;
		}
		op1 = cubos[i] + come(res, cubos, x, y);

		if (cubos[j - 1] > cubos[i]) {
			y = j - 2; x = i;
		}
		else {
			x = i + 1; y = j - 1;
		}
		op2 = cubos[j] + come(res, cubos, x, y);

		res[i][j] = max(op1, op2);
	}
	return res[i][j];
}

bool tratar_caso() {
	int N;
	cin >> N;
	if (N == 0) return false;
	vector<int> cubos(N);
	for (int i = 0; i < N; i++) {
		cin >> cubos[i];
	}

	vector<int>f(N, -1);
	vector<vector<int>>res(N, f);
	cout << come(res, cubos, 0, N - 1) << "\n";
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