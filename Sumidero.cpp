#ifndef DIGRAFO_H_
#define DIGRAFO_H_

#include <iostream>
#include <stdexcept>
#include <vector>

using Adys = std::vector<int>;  // lista de adyacentes a un vértice

class Digrafo {

    int _V;   // número de vértices
    int _A;   // número de aristas
    std::vector<Adys> _ady;   // vector de listas de adyacentes

public:

    /**
     * Crea un grafo dirigido con V vértices.
     */
    Digrafo(int V) : _V(V), _A(0), _ady(_V) {}

    /**
     * Crea un grafo dirigido a partir de los datos en el flujo de entrada (si puede).
     * primer es el índice del primer vértice del grafo en el entrada.
     */
    Digrafo(std::istream& flujo, int primer = 0) : _A(0) {
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
     * Añade la arista dirigida v-w al grafo.
     * @throws domain_error si algún vértice no existe
     */
    void ponArista(int v, int w) {
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::domain_error("Vertice inexistente");
        ++_A;
        _ady[v].push_back(w);
    }


    /**
     * Comprueba si hay arista de u a v.
     */
    bool hayArista(int u, int v) const {
        for (int w : _ady[u])
            if (w == v) return true;
        return false;
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
     * Devuelve el grafo dirigido inverso.
     */
    Digrafo inverso() const {
        Digrafo inv(_V);
        for (int v = 0; v < _V; ++v) {
            for (int w : _ady[v]) {
                inv.ponArista(w, v);
            }
        }
        return inv;
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
 * Para mostrar grafos por la salida estándar.
 */
inline std::ostream& operator<<(std::ostream& o, Digrafo const& g) {
    g.print(o);
    return o;
}


#endif /* DIGRAFO_H_ */

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

class Sumidero {
public:
    Sumidero(const Digrafo& g) :
        visit(g.V(), false), gradSal(g.V(), 0), gradEnt(g.V(), 0), sumidero(-1) {
        for (int v = 0; v < g.V(); v++) {
            if (!visit[v])
                anchura(g, v);
        }
        checkSumidero();
    }

    int res() { return sumidero; }
private:
    vector<bool>visit;
    vector<int> gradSal;
    vector<int> gradEnt;
    int sumidero;

    void anchura(const Digrafo& g, int s) {
        queue<int>q;
        int v = s;
        visit[v] = true;
        q.push(v);
        while (!q.empty()) {
            v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    visit[w] = true;
                    q.push(w);
                }
                gradSal[v]++;
                gradEnt[w]++;
            }
        }
    }

    void checkSumidero() {
        int i = 0;
        while (i < gradSal.size() && sumidero == -1) {
            if (gradSal[i] == 0 && gradEnt[i] == gradSal.size()-1)
                sumidero = i;
            i++;
        }
    }
};


bool tratar_caso() {
    int n, a, v, w;
    cin >> n >> a;
    if (!cin) return false;

    Digrafo g(n);
    for (int i = 0; i < a; i++) {
        cin >> v >> w;
        g.ponArista(v, w);
    }
    Sumidero s(g);
    int sumi = s.res();
    if (sumi != -1)
        cout << "SI " << sumi;
    else
        cout << "NO";
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