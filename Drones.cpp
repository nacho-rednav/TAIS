#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
using namespace std;


bool tratar_caso() {
	int n, n9, n15, aux1, aux2, i, horas;
	priority_queue<int> v9, v15;
	vector<int> s9, s15;

	cin >> n;
	if (!cin) return false;
	cin >> n9 >> n15;

	for (int i = 0; i < n9; i++) {
		cin >> aux1;
		v9.push(aux1);
	}
	for (int i = 0; i < n15; i++) {
		cin >> aux1;
		v15.push(aux1);
	}

	horas = 0;
	while (!v9.empty() && !v15.empty()) {
		i = 0;
		horas = 0;
		while (!v9.empty() && !v15.empty() && i < n) {
			aux1 = v9.top();
			aux2 = v15.top();
			v9.pop(); v15.pop();
			horas += min(aux1, aux2);
			if (aux1 < aux2) {
				s15.push_back(aux2 - aux1);
			}
			else if (aux2 < aux1) {
				s9.push_back(aux1 - aux2);
			}
			i++;
		}
		cout << horas << " ";
		for (int j = 0; j < s9.size(); j++) {
			v9.push(s9[j]);
		}
		for (int j = 0; j < s15.size(); j++) {
			v15.push(s15[j]);
		}
		s9.clear(); s15.clear();
	}
	cout << "\n";

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