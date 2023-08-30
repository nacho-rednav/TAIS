#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <algorithm>
struct Cordel {
	int l, c;

	Cordel(): l(0), c(0){}
	Cordel(int lo, int co) :l(lo), c(co) {}

	bool operator< (const Cordel& c) const {
		return l < c.l;
	}
};



const long long int INF = numeric_limits<long long int>::max() - 10000;

vector<long long int> resuelve(const vector<Cordel>& cords, int L) {
	int n = cords.size();
	vector<long long int>vf(L + 1, 0);
	vector<long long int>vn(L + 1, INF);
	vector<long long int>vc(L + 1, INF);

	vf[0] = 1;
	vn[0] = 0;
	vc[0] = 0;

	for (int i = 1; i < n; i++) {
		for (int j = L; j >= cords[i].l; j--) {
			vf[j] = vf[j] + vf[j - cords[i].l];
			vn[j] = min(vn[j], vn[j - cords[i].l] + 1);
			vc[j] = min(vc[j], vc[j - cords[i].l] + cords[i].c);
		}
	}
	vector<long long>res{ vf[L], vn[L], vc[L] };
	return res;
}

bool tratar_caso() {
	int N, L, l, c;
	cin >> N >> L;
	if (!cin) return false;
	vector<Cordel>cordeles;
	cordeles.push_back({ 0, 0 });
	for (int i = 0; i < N; i++) {
		cin >> l >> c;
		cordeles.push_back({ l, c });
	}
	sort(cordeles.begin(), cordeles.end());

	vector<long long int> res = resuelve(cordeles, L);
	
	if (res[0] > 0) {
		cout << "SI " << res[0] << " " << res[1] << " " << res[2] << "\n";
	}
	else {
		cout << "NO\n";
	}
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
j es la longitud cubierta
i representa el conjunto de cordeles desde el 1 hasta el i


formas(0, j) = 0 con j > 0
formas(i, 0) = 1
formas(i, j) = { formas(i - 1, j) cordeles[i].l > j
			 = { formas(i - 1, j) + formas(i - 1, j - cordeles[i].l)
*/


long long int formas(const vector<Cordel>& cords, int L) {
	int n = cords.size();
	vector<long long>v(L + 1, 0);
	v[0] = 1;

	for (int i = 1; i < n; i++) {
		for (int j = L; j >= cords[i].l; j--) {
			v[j] = v[j] + v[j - cords[i].l];
		}
	}
	return v[L];
}

/*

num(0, j) = INF j > 0
num(i, 0) = 0
num(i, j) = { num(i - 1, j) cordeles[i].l > j
		  = { min(num(i - 1, j), num(i - 1, j - cordeles[i].l) + 1)

*/

int num(const vector<Cordel>& cords, int L) {
	int n = cords.size();
	vector<int> v(L + 1, INF);
	v[0] = 0;
	for (int i = 1; i < n; i++) {
		for (int j = L; j >= cords[i].l; j--) {
			v[j] = min(v[j], v[j - cords[i].l] + 1);
		}
	}
	return v[L];
}

/*

coste(0, j) = INF con j > 0
coste(i, 0) = 0
coste(i, j) = { coste(i-1, j) cordeles[i].l > j
			= { min(coste(i-1, j), coste(i-1, j-cordeles[i].l) + cordeles[i].c)

*/


int coste(const vector<Cordel>& cords, int L) {
	int n = cords.size();
	vector<int> v(L + 1, INF);
	v[0] = 0;
	for (int i = 1; i < n; i++) {
		for (int j = L; j >= cords[i].l; j--) {
			v[j] = min(v[j], v[j - cords[i].l] + cords[i].c);
		}
	}
	return v[L];
}