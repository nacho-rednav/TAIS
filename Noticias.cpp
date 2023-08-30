//
//  Grafo.h
//
//  Implementación de grafos no dirigidos
//
//  Facultad de Informática
//  Universidad Complutense de Madrid
//
//  Copyright (c) 2020  Alberto Verdejo
//

#ifndef GRAFO_H_
#define GRAFO_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <stdexcept>

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class Grafo {
private:
    int _V;  // número de vértices
    int _A;  // número de aristas
    std::vector<Adys> _ady;  // vector de listas de adyacentes
public:

/**
 * Crea un grafo con V vértices.
 */
Grafo(int V) : _V(V), _A(0), _ady(_V) {}

/**
 * Crea un grafo a partir de los datos en el flujo de entrada (si puede).
 * primer es el índice del primer vértice del grafo en el entrada.
 */
Grafo(std::istream& flujo, int primer = 0) : _A(0) {
    flujo >> _V;
    if (!flujo) return;
    _ady.resize(_V);
    int E, v, w;
    flujo >> E;
    while (E--) {
        flujo >> v >> w;
        ponArista(v - primer, w - primer);
    }
}

/**
 * Devuelve el número de vértices del grafo.
 */
int V() const { return _V; }

/**
 * Devuelve el número de aristas del grafo.
 */
int A() const { return _A; }

/**
 * Añade la arista v-w al grafo.
 * @throws domain_error si algún vértice no existe
 */
void ponArista(int v, int w) {
    if (v < 0 || v >= _V || w < 0 || w >= _V)
        throw std::domain_error("Vertice inexistente");
    ++_A;
    _ady[v].push_back(w);
    _ady[w].push_back(v);
}

/**
 * Devuelve la lista de adyacencia de v.
 * @throws domain_error si v no existe
 */
Adys const& ady(int v) const {
    if (v < 0 || v >= _V)
        throw std::domain_error("Vertice inexistente");
    return _ady[v];
}

/**
 * Muestra el grafo en el stream de salida o (para depurar)
 */
void print(std::ostream& o = std::cout) const {
    o << _V << " vértices, " << _A << " aristas\n";
    for (int v = 0; v < _V; ++v) {
        o << v << ": ";
        for (int w : _ady[v]) {
            o << w << " ";
        }
        o << "\n";
    }
}
};
/**
 * Para mostrar grafos por la salida estándar
 */
inline std::ostream& operator<<(std::ostream& o, Grafo const& g) {
    g.print(o);
    return o;
}

#endif /* GRAFO_H_ */

#include <vector>
using namespace std;

class RedSocial {
private:
    vector<bool> visit;
    vector<int> tamConexa;
    vector<int> verticEnConexa;

    void infoConexa(const Grafo& g, int& tam, int v, int nConexa) {
        visit[v] = true;
        verticEnConexa[v] = nConexa;
        tam++;
        for (int w : g.ady(v)) {
            if (!visit[w]) {
                infoConexa(g, tam, w, nConexa);
            }
        }
    }
public:
    RedSocial(const Grafo& g) : // (V * (V + A))
        visit(g.V(), false), tamConexa(), verticEnConexa(g.V(), -1) {
        int t = 0;
        int conexa = 0;
        for (int v = 0; v < g.V(); v++) { //O(V)
            if (!visit[v]) {
                infoConexa(g, t, v, conexa); //O(V + A)
                tamConexa.push_back(t);
                conexa++;
            }
            t = 0;
        }
    }

    void res() {
        for (int d : verticEnConexa) { //O(V)
            cout << tamConexa[d] << " ";
        }
        cout << "\n";
    }
};

bool tratar_caso() {
    int N, G, tamg, v1, w;
    cin >> N >> G;

    if (!cin)
        return false;
    Grafo gr(N);

    for (int g = 0; g < G; g++) {
        cin >> tamg;
        if (tamg > 0) cin >> v1;
        for (int i = 1; i < tamg; i++) {
            cin >> w;
            gr.ponArista(v1-1, w-1);
        }
    }

    RedSocial r(gr);
    r.res();

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