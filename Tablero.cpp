#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <utility>
#include <algorithm>
/*
i = coordenada eje Y tablero
j = coordenada eje X tablero
juego devuelve la máxima puntuación que se puede obtener
partiendo desde (i, j)

juego(0, j) = 0
juego(i, j) = 0 si j > N
juego(i, j) = { tablero[i][j] + max(juego(i-1, j-1), juego(i-1, j), juego(i-1, j+1) 1 <= i, j <= N

*/

pair<int, int>juego(const vector<vector<int>>& tablero, int N) {
	vector<int>res(N + 2); res[0] = 0; res[N - 1] = 0;
	for (int i = 1; i <= N; i++)
		res[i] = tablero[0][i];
	int iz, ar, der, prev;
	for (int f = 1; f < N; f++) {
		prev = 0;
		for (int c = 1; c <= N; c++) {
			iz = prev;
			ar = res[c];
			der = res[c + 1];
			prev = res[c];
			res[c] = tablero[f][c] + max(iz, max(ar, der));
		}
	}
	int max, col;
	col = 1; max = res[col];
	for (int i = 2; i <= N; i++) {
		if (res[i] > max) {
			max = res[i];
			col = i;
		}
	}
	return { max, col };
}

bool tratar_caso() {
	int N;
	cin >> N;
	if (!cin)return false;
	vector<int>f(N+1, 0);
	vector<vector<int>>tablero(N, f);
	for (int i = 0; i < N; i++)
		for(int j = 1; j <= N; j++)
			cin >> tablero[i][j];
	
	auto p = juego(tablero, N);
	cout << p.first << " " << p.second << "\n";

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