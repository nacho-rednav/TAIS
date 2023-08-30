#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <unordered_map>
#include <string>

#ifndef ENTEROSINF_H_
#define ENTEROSINF_H_

#include <limits>
#include <iostream>


class EntInf {
	int num;
public:
	static const int _intInf = 1000000000;

	EntInf(int n = 0) : num(n) {}

	EntInf operator+(EntInf const& b) const {
		if (num == _intInf || b.num == _intInf || num >= (_intInf - b.num))
			return _intInf;
		else return num + b.num;
	}

	bool operator==(EntInf const& b) const {
		return num == b.num;
	}

	bool operator!=(EntInf const& b) const {
		return !(*this == b);
	}

	bool operator<(EntInf const& b) const {
		if (num == _intInf) return false;
		else if (b.num == _intInf) return true;
		else return num < b.num;
	}

	bool operator>(EntInf const& b) const {
		return b < *this;
	}

	void print(std::ostream& out = std::cout) const {
		if (num == _intInf) out << "+Inf";
		else out << num;
	}
};

const EntInf Infinito(EntInf::_intInf);

inline std::ostream& operator<<(std::ostream& out, EntInf const& e) {
	e.print(out);
	return out;
}

#endif

EntInf grado( vector<vector<EntInf>>& C) {
	int v = C.size();
	
	for(int k = 0; k < v; k++)
		for(int i = 0; i < v; i++)
			for (int j = 0; j < v; j++) {
				auto temp = C[i][k] + C[k][j];
				if (temp < C[i][j]) {
					C[i][j] = temp;
				}
			}
	auto maxi = C[0][0];
	int i = 0, j = 0;
	bool stop = false;
	while (i < v && !stop) {
		j = 0;
		while (j < v && !stop) {
			maxi = max(maxi, C[i][j]);
			if (maxi == Infinito) {
				stop = true;
				maxi = Infinito;
			}
			j++;
		}
		i++;
	}
	return maxi;
}

bool tratar_caso() {
	int V, A, ind = 0;
	string d, o;
	cin >> V >> A;
	if (!cin)return false;
	unordered_map<string, int> indx;
	vector<EntInf> f(V, Infinito);
	vector<vector<EntInf>> G(V, f);
	for (int i = 0; i < A; i++) {
		cin >> d >> o;
		if (indx.count(d) == 0) { indx[d] = ind; ind++;}
		if (indx.count(o) == 0) { indx[o] = ind; ind++;}
		G[indx[d]][indx[o]] = 1;
		G[indx[o]][indx[d]] = 1;
	}
	for (int i = 0; i < V; i++)
		G[i][i] = 0;

	auto res = grado(G);
	if (res == Infinito) cout << "DESCONECTADA";
	else cout << res;
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