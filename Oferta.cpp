#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <algorithm>

bool comp(int i, int j) { return i > j; }

bool tratar_caso() {
	int N; cin >> N;
	if (!cin) return false;
	vector<int>libros(N);
	for (int i = 0; i < N; i++) {
		cin >> libros[i];
	}
	sort(libros.begin(), libros.end(), comp);

	int sum = 0;
	for (int i = 2; i < N; i += 3) {
		sum += libros[i];
	}
	cout << sum << "\n";
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