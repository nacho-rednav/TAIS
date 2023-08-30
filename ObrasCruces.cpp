#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <string>

/*
* i = coordenada norte-sur ciudad
* j = coordenada este-oeste ciudad

Caminos calcula el número de formas que hay de llegar a la
coordenada i, j sin pasar por obras y sólol avanzando hacia el sur
o el este, para que sea el camino más corto posible
caminos(1, 1) = 1
caminos(1, j) = { 0 si obras[1][j] 
			  = { caminos(1, j-1)
caminos(i, 1) = { 0 si obras[i][1] || obras[i-1][1]
			  = { caminos(i-1, 1)

caminos(i, j) = { 0 si obras[i][j]
			  = { caminos(i-1, j) + caminos(i, j-1)


*/

int caminos(const vector<vector<bool>>& obras, int N, int M) {
	vector<int> res(M, 1);
	for (int i = 1; i < M; i++) {
		if (obras[0][i]) res[i] = 0;
		else res[i] = res[i - 1];
	}
	
	for (int i = 1; i < N; i++) {
		if (obras[i][0]) res[0] = 0;

		for (int j = 1; j < M; j++) {
			if (!obras[i][j]) {
				res[j] = res[j] + res[j - 1];
			}
			else {
				res[j] = 0;
			}
		}
	}
	return res[M - 1];
}

bool tratar_caso() {
	int N, M;
	string aux;
	cin >> N >> M;
	if (!cin)return false;
	vector<bool>f(M, false);
	vector<vector<bool>> obras(N, f);
	cin.ignore();
	for (int i = 0; i < N; i++) {
		getline(cin, aux);
		for (int j = 0; j < M; j++) {
			obras[i][j] = (aux[j] == 'X');
		}
	}
	cout << caminos(obras, N, M) << "\n";
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