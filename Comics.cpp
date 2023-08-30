#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <queue>
#include <stack>

struct ComicStack {
	stack<int> pila;

	bool operator<(const ComicStack& c) const {
		return c.pila.top() < pila.top();
	}
};

bool tratar_caso() {
	int P, N, id, minim;
	cin >> P;
	if (!cin)return false;
	priority_queue<ComicStack>comics;
	ComicStack c_pila;
	ComicStack aux;
	minim = numeric_limits<int>::max();
	for (int i = 0; i < P; i++) {
		cin >> N;
		c_pila = aux;
		for (int j = 1; j <= N; j++) {
			cin >> id;
			minim = min(minim, id);
			c_pila.pila.push(id);
		}
		comics.push(c_pila);
	}
	int cont = 1;

	while (comics.top().pila.top() != minim) {
		cont++;
		aux = comics.top();
		comics.pop();
		aux.pila.pop();
		if(!aux.pila.empty())
			comics.push(aux);
	}

	cout << cont << "\n";

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