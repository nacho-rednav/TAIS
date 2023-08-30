#ifndef CONJUNTOSDISJUNTOS_H_
#define CONJUNTOSDISJUNTOS_H_

#include <vector>
#include <iostream>

class ConjuntosDisjuntos {
protected:
    int ncjtos;  // número de conjuntos disjuntos
    mutable std::vector<int> p;  // enlace al padre
    std::vector<int> tam;  // tamaño de los árboles
public:

    // crea una estructura de partición con los elementos 0..N-1,
    // cada uno en un conjunto, partición unitaria
    ConjuntosDisjuntos(int N) : ncjtos(N), p(N), tam(N, 1) {
        for (int i = 0; i < N; ++i)
            p[i] = i;
    }

    //  devuelve el representante del conjunto que contiene a a
    int buscar(int a) const {
        if (p.at(a) == a) // es una raíz
            return a;
        else
            return p[a] = buscar(p[a]);
    }

    // unir los conjuntos que contengan a a y b
    void unir(int a, int b) {
        int i = buscar(a);
        int j = buscar(b);
        if (i == j) return;
        if (tam[i] > tam[j]) { // i es la raíz del árbol más grande
            tam[i] += tam[j]; p[j] = i;
        }
        else {
            tam[j] += tam[i]; p[i] = j;
        }
        --ncjtos;
    }

    // devuelve si a y b están en el mismo conjunto
    bool unidos(int a, int b) const {
        return buscar(a) == buscar(b);
    }

    // devuelve el número de elementos en el conjunto de a
    int cardinal(int a) const {
        return tam[buscar(a)];
    }

    // devuelve el número de conjuntos disjuntos
    int num_cjtos() const { return ncjtos; }

};

#endif

#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include<string>
#include <utility>


void uniones(ConjuntosDisjuntos& m, vector<string>& map, int f, int c, int C, int F) { //O(log*F*C) -> O(1)
    vector<pair<int, int>>dirs = { {0, -1}, {-1, -1}, {-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1} };
    int faux, caux;
    for (auto dir : dirs) {
        faux = f + dir.first;
        caux = c + dir.second;
        if (faux >= 0 && caux >= 0 && 
            faux < F && caux < C &&
            map[faux][caux] == '#' &&
            !m.unidos(f * C + c, faux * C + caux)) {
            m.unir(f * C + c, faux * C + caux);
        }
    }
}

bool tratar_caso() {
    int F, C, k, f, c, faux, caux, maximo;
    string line;
    cin >> F >> C;
    if (!cin)return false;
    vector<string>map;
    ConjuntosDisjuntos manchas(F * C);

    cin.ignore();
    for (int i = 0; i < F; i++) {
        getline(cin, line);
        map.push_back(line);
    }
    maximo = 0;
    for (int f = 0; f < F; f++) {
        for (int c = 0; c < C; c++) {   //O(F*C)
            if (map[f][c] == '#') {
                uniones(manchas, map, f, c, C, F);
                maximo = max(maximo, manchas.cardinal(f * C + c));
            }
        }
    }
    cout << maximo << " ";
    cin >> k;
    for (int i = 0; i < k; i++) { //O(K)
        cin >> f >> c;
        f--; c--;
        map[f][c] = '#';
        uniones(manchas, map, f, c, C, F);
        maximo = max(maximo, manchas.cardinal(f * C + c));
        cout << maximo << " ";
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