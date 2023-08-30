#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <algorithm>
/*

trozos(i, j) = maximo numero de dias en que podremos comer trozos iguales
			   con los trozos del i al j

trozos(i, i) = 0

trozos(i , j) = { max(trozos(i+2, j) + check(i, i+1, pastel) , trozos(i+1, j-1) + check(i, j, pastel), trozos(i, j-2) + check(j, j-1, pastel)


check(i, j, pastel){
	if(pastel[i] == pastel[j] && pastel[i] != 0) return 1
	return 0
}
*/

int check(int i, int j, const vector<int>& v) {
	if (v[i] == v[j] && v[i] != 0) return 1;
	return 0;
}

int resolver(const vector<int>& v, int N) {
	vector<vector<int>>res(N, vector<int>(N, 0));

	for (int i = 0; i < N - 1; i++) {
		int j = i + 1;
		res[i][j] = check(i, j, v);
	}

	for (int d = 2; d < N; d++) {
		for (int i = 0; i < N - d; i++) {
			int j = i + d;
			res[i][j] = max(res[i + 2][j] + check(i, i + 1, v), max(res[i + 1][j - 1] + check(i, j, v), res[i][j - 2] + check(j, j - 1, v)));
		}
	}
	return res[0][N - 1];
}

bool tratar_caso() {
	int N;
	cin >> N;
	if (!cin)return false;
	vector<int>pastel(N);
	for (int i = 0; i < N; i++) cin >> pastel[i];

	cout << resolver(pastel, N) << "\n";
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