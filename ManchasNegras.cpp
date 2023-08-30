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

using namespace std;
#include <vector>
#include <utility>

class MachasNegras { //Buscar componente conexa mas grande
public:
    MachasNegras(const Grafo& g) :
        visit(g.V(), false), maxi(0), nmanchas(0){
        int tam = 0;
        for (int v = 0; v < g.V(); v++) {
            if (!visit[v]) {
                nmanchas++;
                tamConexa(g, tam, v);
                maxi = max(maxi, tam);
                tam = 0;
            }
        }
    }
    int maximo() {
        return maxi;
    }
    int cuantas() {
        return nmanchas;
    }
private:
    vector<bool>visit;
    int maxi;
    int nmanchas;

    void tamConexa(const Grafo& g, int& t, int v) {

        visit[v] = true;
        t++;
        for (int w : g.ady(v)) {
            if (!visit[w]) {
                tamConexa(g, t, w);
            }
        }
    }

};

bool tratar_caso() {
    int F, C;
    int v = 0;
    char elem;
    vector<pair<int, int>> aristas;
    cin >> F >> C;

    if (!cin)
        return false;
    vector<int>fila(C, -1);

    for (int f = 0; f < F; f++) {
        cin >> elem;
        if (elem == '-') {
            fila[0] = -1;
        }
        else {
            if (fila[0] != -1) { //Arista con el de arriba
                aristas.push_back({ fila[0], v });
            }
            fila[0] = v;
            v++;
        }
        for (int c = 1; c < C; c++) {
            cin >> elem;
            if (elem == '-') {
                fila[c] = -1;
            }
            else {
                if (fila[c] != -1) { //Arista con el de arriba
                    aristas.push_back({ fila[c], v });
                }
                if (fila[c - 1] != -1) { //Arista con el de detr�s
                    aristas.push_back({ fila[c - 1], v });
                }
                fila[c] = v;
                v++;
            }
        }
    }

    Grafo g(v);

    for (auto p : aristas) {
        g.ponArista(p.first, p.second);
    }

    MachasNegras m(g);

    cout << m.cuantas() << " " << m.maximo() << "\n";

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