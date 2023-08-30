#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <string>
#include <utility>
/*
pal(i,j) = numero minimo de letras añadidas a la palabra que va de i a j
			para formar un palindromo

pal(i, j) = 0 si i == j
pal(i, j) = 0 si i > j
pal(i, j) = { pal(i+1, j-1) si palabra[i] == palabra[j]
		  = { min(pal(i, j-1)+1, palabra(i+1, j) + 1)

*/

int pal(int i, int j, const string p, vector<vector<int>>& res) {
	if (res[i][j] != -1) return res[i][j];

	if (i == j) res[i][j] = 0;
	else if (i > j) res[i][j] = 0;
	else if (p[i] == p[j]) res[i][j] = pal(i + 1, j - 1, p, res);
	else {
		res[i][j] = min(pal(i + 1, j, p, res) + 1, pal(i, j - 1, p, res) + 1);
	}
	return res[i][j];
}

void rec_sol(const string p, const vector<vector<int>>& res,int i, int j, string& sol) {

	if (i > j) return;

	if (p[i] == p[j]) {
		sol.push_back(p[i]);
		rec_sol(p, res, i + 1, j - 1, sol);
		if(i != j)
			sol.push_back( p[j] );
	}
	else if (res[i][j] == res[i][j - 1] + 1) {
		sol.push_back(p[j]);
		rec_sol(p, res, i, j - 1, sol);
		sol.push_back(p[j]);
	}
	else {
		sol.push_back(p[i]);
		rec_sol(p, res, i + 1, j, sol);
		sol.push_back(p[i]);
	}
}

pair<int, string> resuelve(string p) {
	int n = p.size();
	string pl = p;
	vector<int> f(n, -1);
	vector<vector<int>>res(n, f);
	int r = pal(0, n - 1, p, res);
	if (r > 0) {
		pl = "";
		rec_sol(p, res, 0, n-1, pl);
	}
	return { r, pl };
}

bool tratar_caso() {
	string p;
	cin >> p;
	if (!cin) return false;
	
	auto res = resuelve(p); 
	cout <<res.first << " " << res.second<< "\n";

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