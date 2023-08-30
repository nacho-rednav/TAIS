#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <utility>
#include <algorithm>
/*
oro(i, j) = cantidad de oro maxima que se puede obtener con los cofres
				del 1 al i con j segundos restantes en la botella


	oro(0, j) = 0 con j > 0
	oro(i, 0) = 0
	oro(i, j) = { oro(i - 1, j) si cofres[i].p > j
			  = { max( oro(i - 1, j),  oro(i - 1, j - cofres[i].p) + cofres[i].oro)

*/


struct Cofre {
	int p;
	int oro;

	void display() {
		cout << p / 3 << " " << oro << "\n";
	}
};

int oro(int i, int j, vector<vector<int>>& res, const vector<Cofre>& cofres) {
	if (res[i][j] != -1) return res[i][j];

	if (i == 0 || j == 0) res[i][j] = 0;
	else if (cofres[i].p > j) res[i][j] = oro(i - 1, j, res, cofres);
	else {
		res[i][j] = max(oro(i - 1, j, res, cofres), oro(i - 1, j - cofres[i].p, res, cofres) + cofres[i].oro);
	}
	return res[i][j];
}

vector<Cofre> reconstruye(const vector<Cofre>& cofres, const vector<vector<int>>& res, int T, int N) {
	vector<Cofre> sol;

	int i = N, j = T;

	while (i > 0 && j > 0) {
		if (cofres[i].p <= j && res[i][j] == cofres[i].oro + res[i - 1][j - cofres[i].p]) {
			sol.push_back(cofres[i]);
			j -= cofres[i].p;
		}
		i--;
	}
	return sol;
}

pair<int, vector<Cofre>> resuelve(int T, int N, const vector<Cofre>& cofres) {
	vector<int> f(T+1, -1);
	vector<vector<int>> res(N+1, f);

	int o = oro(N, T, res, cofres);
	vector<Cofre> sol = reconstruye(cofres, res, T, N);

	return { o, sol };
}

bool tratar_caso() {
	int T, N, p, o;
	cin >> T >> N;
	if (!cin) return false;
	vector<Cofre> cofres(N+1);
	for (int i = 1; i <= N; i++) {
		cin >> p >> o;
		cofres[i] = { 3*p, o };
	}
	auto par = resuelve(T, N, cofres);
	cout << par.first << "\n" << par.second.size() << "\n";
	for (int i = par.second.size() - 1; i >= 0; i--)
		par.second[i].display();
	cout << "---\n";
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