#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <algorithm>

int resuelve(const vector<int>& ninos, const vector<int>& camis) {
	int res = 0, N = ninos.size(), M = camis.size();
	int i = 0, j = 0;
	while (i < N && j < M) {
		if (camis[j] == ninos[i] || camis[j] - ninos[i] == 1) {
			//Le vale la camiseta
			i++; j++;
		}
		else if (camis[j] < ninos[i]) {
			//Camiseta pequeña
			j++;
		}
		else if(camis[j] > ninos[i] + 1){
			//Camiseta demasiado grande
			res++; i++;
		}
	}
	if (i < N) {
		res += N - i;
	}
	return res;
}

bool tratar_caso() {
	int N, M, aux;
	vector<int> ninos, camis;
	cin >> N >> M;
	if (!cin)return false;
	for (int i = 0; i < N; i++) {
		cin >> aux; ninos.push_back(aux);
	}
	for (int i = 0; i < M; i++) {
		cin >> aux; camis.push_back(aux);
	}
	sort(ninos.begin(), ninos.end());
	sort(camis.begin(), camis.end());

	cout << resuelve(ninos, camis) << "\n";
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