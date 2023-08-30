#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <queue>
using namespace std;

long long calcular_esfuerzo(priority_queue<long long, vector<long long>, greater<long long>>& elems) {
	long long esfuerzo = 0;
	long long a, b, s;

	while (elems.size() > 1) {
		a = elems.top();
		elems.pop();
		b = elems.top();
		elems.pop();
		s = a + b;
		esfuerzo += s;
		elems.push(s);
	}

	return esfuerzo;
}

bool tratar_caso() {
	int n;
	long long aux;
	priority_queue<long long, vector<long long>, greater<long long>> elems;

	cin >> n;
	if (n == 0) return false;
	for (int i = 0; i < n; i++) {
		cin >> aux;
		elems.push(aux);
	}
	cout << calcular_esfuerzo(elems) << "\n";
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