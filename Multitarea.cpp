#include <iostream>
#include <fstream>
#include <queue>
using namespace std;

struct tarea {
	int inicio;
	int fin;
	int periodo;

	bool operator<(const tarea& t) const {
		return t.inicio < inicio;
	}
	bool solapa(const tarea& t) const {
		return t.inicio < fin;
	}
	void avanza() {
		inicio += periodo;
		fin += periodo;
	}
};

bool comprueba_correcto(priority_queue<tarea>& tareas, int t) {
	bool correcto = true;
	tarea ta;

	while (correcto && tareas.size() > 1) {
		ta = tareas.top();
		tareas.pop();
		if (ta.solapa(tareas.top())) correcto = false;

		ta.avanza();
		if (ta.inicio < t) tareas.push(ta);
	}

	return correcto;
}

bool tratar_caso() {
	int n, m, t;
	tarea ta;
	priority_queue<tarea> tareas;
	cin >> n;
	if (!std::cin) return false;
	cin >> m >> t;
	for (int i = 0; i < n; i++) {
		cin >> ta.inicio >> ta.fin;
		ta.periodo = t + 1;
		if(ta.inicio < t)
			tareas.push(ta);
	}
	for (int i = 0; i < m; i++) {
		cin >> ta.inicio >> ta.fin >> ta.periodo;
		if (ta.inicio < t)
			tareas.push(ta);
	}

	cout << (comprueba_correcto(tareas, t) ? "NO" : "SI") << "\n";
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