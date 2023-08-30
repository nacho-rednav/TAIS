#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <algorithm>




bool tratar_caso() {
	int N;
	cin >> N;
	if (N == 0) return false;

	vector<int>alturas(N);
	vector<int>esquis(N);
	for (int i = 0; i < N; i++)
		cin >> alturas[i];
	for (int i = 0; i < N; i++)
		cin >> esquis[i];

	sort(alturas.begin(), alturas.end());
	sort(esquis.begin(), esquis.end());

	int sum = 0;

	for (int i = 0; i < N; i++) {
		sum += abs(alturas[i] - esquis[i]);
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