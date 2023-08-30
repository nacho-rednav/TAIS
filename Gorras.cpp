#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <queue>

bool tratar_caso() {
	int N;
	long long int aux, sum, aux2;
	cin >> N;
	if (N == 0) return false;
	
	priority_queue<long long int, vector<long long int>, greater<long long int>> equipos;

	for (int i = 0; i < N; i++) {
		cin >> aux;
		equipos.push(aux);
	}

	sum = 0;
	while (equipos.size() > 1) {
		aux = equipos.top();
		equipos.pop();
		aux2 = equipos.top();
		equipos.pop();
		equipos.push(aux + aux2);
		sum += (aux + aux2);
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