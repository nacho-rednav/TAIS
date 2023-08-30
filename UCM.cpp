#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct usuario {
	int id;
	int turno;
	int periodo;

	bool operator<(const usuario& b) const{
		return (b.turno < turno) ||
			(b.turno == turno && b.id < id);
	}
};

bool tratar_caso() {
	int n = 0;
	usuario s;
	priority_queue<usuario> ucm;
	cin >> n;
	if (n == 0) return false;
	for (int i = 0; i < n; i++) {
		cin >> s.id >> s.turno;
		s.periodo = s.turno;
		ucm.push(s);
	}
	n = 0;
	cin >> n;
	for (int i = 0; i < n; i++) {
		s = ucm.top();
		ucm.pop();
		s.turno += s.periodo;
		ucm.push(s);
		cout << s.id << "\n";
	}
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