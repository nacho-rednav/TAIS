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

int resolver(const vector<vector<int>>& m, int N, int M) {
    int blanco = 0;
    int negro = -1;
    ConjuntosDisjuntos res(N * M);

    for (int i = 0; i < M; i++) {
        res.unir(i, blanco);
    }

    for (int f = 1; f < N; f++) {
        res.unir(blanco, f * M);
        for (int c = 1; c < M; c++) {
            if (m[f][c] == 0){
                if (m[f][c - 1] == 0) {
                    res.unir(f * M + c, f * M + (c - 1));
                }
                if (m[f - 1][c] == 0) {
                    res.unir(f * M + c, (f-1) * M + c);
                }
            }
            else if (m[f][c] == 1) {
                if (negro != -1) {
                    res.unir(negro, f * M + c);
                }
                else
                    negro = f * M + c;
            }
        }
    }
    return max(0, res.num_cjtos() - 2);
}

bool tratar_caso() {
    int N, M;
    char aux;
    cin >> M >> N;
    if (!cin) return false;
    vector<vector<int>>mapa(N, vector<int>(M, 0));
    for (int f = 0; f < N; f++) {
        for (int c = 0; c < M; c++) {
            cin >> aux;
            if (aux == 'X')
                mapa[f][c] = 1;
        }
    }
    cout << resolver(mapa, N, M) << "\n";
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