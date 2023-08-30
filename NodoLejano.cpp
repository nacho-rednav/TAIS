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

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

class InspectorRedes {
private:
    vector <int> dist;
    int s;

    void inspeccion(const Grafo& g) {
        vector<bool> visit(g.V(), false);
        queue<int> cola;
        int v = s;
        visit[v] = true;
        dist[v] = 0;
        cola.push(v);
        while (!cola.empty()) {
            v = cola.front(); cola.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    visit[w] = true;
                    dist[w] = dist[v] + 1;
                    cola.push(w);
                }
            }
        }
    }
public:
    InspectorRedes(const Grafo& g, int s) :
        dist(g.V(), -1), s(s) {
        inspeccion(g);
    }

    void res(int ttl) {
        int resu = 0;
        for (int i = 0; i < dist.size(); i++) {
            if (dist[i] > ttl || dist[i] == -1) {
                resu++;
            }
        }
        cout << resu << "\n";
    }

    int raiz() { return s; }
};

bool tratar_caso() {
    int N, C, K;
    int v, w, ttl;
    InspectorRedes* insp;

    cin >> N >> C;
    if (!cin)
        return false;
    Grafo g(N);
    for (int i = 0; i < C; i++) {
        cin >> v >> w;
        g.ponArista(v - 1, w - 1);
    }
    cin >> K;
    cin >> v >> ttl;
    v--;
    insp = new InspectorRedes(g, v);
    insp->res(ttl);
    for (int i = 1; i < K; i++) {
        cin >> v >> ttl;
        v--;
        if (v != insp->raiz()) {
            delete insp;
            insp = new InspectorRedes(g, v); //O(V + A)
        }
        insp->res(ttl);//O(V)
    }
    cout << "---\n";
    delete insp;
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