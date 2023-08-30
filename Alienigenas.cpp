#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <algorithm>


/*
Solucion X voraz e Y óptima

La solución voraz elige el trabajo que termina lo más tarde posible mientras
sea admisible, osea, su comienzo engancha con otro trabajo.
Al encontrar una diferencia siempre ocurrirá que en la Y termina en el mismo punto
o antes que el que ha elegido la solución X. Todo lo anterior en las soluciones era igual por lo
que ambos trabajos enganchan con el anterior. Entonces, como la opción que ha elegido X terminará más tarde o igual
que la elegida por Y, podemos hacer el cambio sin arriesgarnos a que vayan a hacer falta más trabajos en Y, porque con este cambio ahora
el nuevo trabajo asignado llega igual o más "lejos"
*/

struct Tarea {
	int ini, fin;
	Tarea(int i, int f) : ini(i), fin(f) {};

	bool operator<(const Tarea& t)const {
		return ini < t.ini ||
			(ini == t.ini && fin < t.fin);
	}
};

int resolver(const vector<Tarea>& t, int C, int F) {
	int res = 0;
	int fin = -1, faux = -1;
	int i;
	for (i = 0; i < t.size(); i++) {
		if (t[i].ini <= C && t[i].fin > fin) {
			fin = t[i].fin;
		}
		else if (t[i].ini > C)break;
	}
	if (fin != -1)res++;
	else return -1;

	if (fin >= F) return res;
	faux = fin;
	for (i; i < t.size(); i++) {
		if (t[i].ini <= fin && t[i].fin > faux) {
			faux = t[i].fin;
		}
		else if (t[i].ini > fin) {
			if (t[i].ini > faux)
				return -1;
			else if(t[i].fin > faux){
				res++;
				fin = faux;
				faux = t[i].fin;
			}
		}
		if (faux >= F) {
			res++;
			fin = faux;
			break;
		}
	}
	if (fin < F) res = -1;
	return res;
}

bool tratar_caso() {
	int C, F, N, i, f;
	cin >> C >> F >> N;
	if (C + F + N == 0) return false;
	vector<Tarea>v;
	for (int j = 0; j < N; j++) {
		cin >> i >> f;
		v.push_back({ i, f });
	}
	sort(v.begin(), v.end());
	int res = resolver(v, C, F);
	if (res > 0)
		cout << res;
	else
		cout << "Imposible";
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

/*
int resolver(const vector<Tarea>& t, int C, int F) {
	int res = 0;
	int fin = -1, faux = -1;
	int i;
	for (i = 0; i < t.size(); i++) {
		if (t[i].ini <= C && t[i].fin > fin) {
			fin = t[i].fin;
		}
		else if (t[i].ini > C)break;
	}
	if (fin != -1)res++;
	else return -1;

	faux = fin;
	bool cand = false;
	for (i; i < t.size(); i++) {
		if (t[i].ini < fin && t[i].fin > faux) {
			cand = true;
			faux = t[i].fin;
		}
		else if (t[i].ini == fin) {
			if (faux < t[i].fin) {
				fin = t[i].fin;
				faux = fin;
				cand = false;
				res++;
			}
		}
		else if (t[i].ini > fin) {
			if (!cand || (cand && faux < t[i].ini))
				return -1;
			else if (cand && faux < t[i].fin) {
				res++;
				if (t[i].ini == faux) {
					fin = t[i].fin;
					faux = fin;
					cand = false;
					res++;
				}
				else if (t[i].ini < faux) {
					fin = faux;
					cand = true;
					faux = t[i].fin;
				}
			}
		}
		if (faux >= F) {
			fin = faux;
			if (cand) res++;
			break;
		}
	}
	if (fin < F) res = -1;
	return res;
}
*/