#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <queue>

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

class Guardias {
private:
    int c;
    bool imposible;

    int toca_color(int c) {
        if (c == 1)return 0;
        return 1;
    }

public:
    Guardias(const Grafo& g) {
        vector<bool> visit(g.V(), false);
        vector<int> marcas(g.V(), -1);
        vector<int> conteo(2, 0);
        imposible = false;
        c = 0;
        queue<int> q;

        for (int i = 0; i < g.V(); i++) {
            if (!visit[i]) {
                visit[i] = true;
                if (g.ady(i).size()>0) {
                    conteo[0] = 0; conteo[1] = 0;
                    q.push(i);
                    marcas[i] = 0;
                    conteo[0]++;
                    while (!q.empty() && !imposible) {
                        int v = q.front(); q.pop();
                        for (int w : g.ady(v)) {
                            if (!visit[w]) {
                                visit[w] = true;
                                marcas[w] = toca_color(marcas[v]);
                                conteo[marcas[w]]++;
                                q.push(w);
                            }
                            else if (visit[w] && marcas[w] == marcas[v]) {
                                imposible = true; break;
                            }
                        }
                    }
                    c += min(conteo[0], conteo[1]);
                }
            }
            if (imposible) break;
        }
    }

    int result() { return c; }
    bool es_imposible() { return imposible; }
};

bool tratar_caso() {
    int V, A, v, w;
    cin >> V >> A;
    if (!cin) return false;
    Grafo g(V);
    for (int i = 0; i < A; i++) {
        cin >> v >> w;
        g.ponArista(v-1, w-1);
    }
    Guardias solve(g);
    if (solve.es_imposible()) cout << "IMPOSIBLE\n";
    else cout << solve.result() << "\n";
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