#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

bool tratar_caso() {
	int n1, p, med, j;
	bool dosMenor = false, dosMayor = false;
	priority_queue<int> menores;
	priority_queue<int, vector<int>, greater<int>> mayores;
	cin >> n1 >> p;
	if (n1 == 0 && p == 0) return false;

	med = n1;
	j = 0;
	for (int i = 0; i < p*2; i++) {
		cin >> n1;

		if (n1 < med) menores.push(n1);
		else mayores.push(n1);

		if (mayores.size() > menores.size()) {
			n1 = med;
			med = mayores.top();
			mayores.pop();
			menores.push(n1);
		}
		else if (menores.size() > mayores.size() + 1) {
			n1 = med;
			med = menores.top();
			menores.pop();
			mayores.push(n1);
		}

		if (j == 1) {
			cout << med << " ";
			j = -1;
		}
		j++;
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