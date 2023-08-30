#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <algorithm>
/*
	vuela(i) = total de formas diferentes en las que se puede llegar al pivote
				i partiendo del primero
	
	vuela(i) = 1 i = 1
	vuela(i) = sum{j = min(1, i-1-V) -> i-2} (vuela(j))

*/

const int MOD = 1000000007;

int resolver(int N, int V) {
	if (V == 0)
		return 1;
	int cont;
	vector<int>res(N + 1, 0);

	res[1] = 1;
	for (int i = 2; i <= N; i++) {
		cont = max(1, i - 1 - V);
		for (int j = i - 1; j >= cont; j--) {
			res[i] = (res[i] + res[j]) % MOD;
		}
	}
	return res[N];
}

bool tratar_caso() {
	int N, V;
	cin >> N >> V;
	if(N + V == 0) return false;

	cout << resolver(N, V) << "\n";
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