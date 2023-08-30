/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
  * Estudiante 1: IGNACIO REDONDO NAVARRO TAIS85
  * Estudiante 2: VICTOR ORTEGO MARTIN TAIS72
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>
#include <stdexcept>

using namespace std;


/*@ <answer>

 Siendo V = número vértices y A = número de aristas del grafo de entrada
 El coste de la solución es O(V + A) porque la solución se obtiene realizando
 un recorrido en profundidad del grafo. Como el grafo está implementado con listas de
 adyacentes el coste será de O(V + A)

 La solución consiste en realizar un recorrido en profundidad para obtener
 de cada componente conexa el precio mínimo que podemos pagar para comenzar un
 rumor dentro de esa componente conexa. Cada precio mínimo se suma para obtener el resultado final

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo (después de la marca)
 //@ <answer>

using Adys = std::vector<int>;  // lista de adyacentes a un vÃ©rtice

class Grafo {
private:
    int _V;  // nÃºmero de vÃ©rtices
    int _A;  // nÃºmero de aristas
    std::vector<Adys> _ady;  // vector de listas de adyacentes
public:

    /**
     * Crea un grafo con V vÃ©rtices.
     */
    Grafo(int V) : _V(V), _A(0), _ady(_V) {}

    /**
     * Crea un grafo a partir de los datos en el flujo de entrada (si puede).
     * primer es el Ã­ndice del primer vÃ©rtice del grafo en el entrada.
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
     * Devuelve el nÃºmero de vÃ©rtices del grafo.
     */
    int V() const { return _V; }

    /**
     * Devuelve el nÃºmero de aristas del grafo.
     */
    int A() const { return _A; }

    /**
     * AÃ±ade la arista v-w al grafo.
     * @throws domain_error si algÃºn vÃ©rtice no existe
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
        o << _V << " vÃ©rtices, " << _A << " aristas\n";
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
 * Para mostrar grafos por la salida estÃ¡ndar
 */
inline std::ostream& operator<<(std::ostream& o, Grafo const& g) {
    g.print(o);
    return o;
}

class Personajes {
private:
    vector<bool> visit;
    int gasto;

    void minConexa(const Grafo& g, const vector<int>& precios, int v, int& mini) {
        visit[v] = true;
        mini = min(precios[v], mini);
        for (int w : g.ady(v)) {
            if (!visit[w]) {
                minConexa(g, precios, w, mini);
            }
        }
    }

public:
    Personajes(const Grafo& g, const vector<int>& precios) : visit(g.V(), false), gasto(0) {
        int min;
        for (int v = 0; v < g.V(); v++) {
            if (!visit[v]) {
                min = precios[v];
                minConexa(g, precios, v, min);
                gasto += min;
            }
        }
    }
    int res() {
        return gasto;
    }

};


bool resuelveCaso() {

    // leemos la entrada
    int N, M, v, w;
    cin >> N >> M;

    if (!cin)
        return false;

    // leer el resto del caso y resolverlo
    Grafo g(N);
    vector<int> precios(N);
    for (int i = 0; i < N; i++) {
        cin >> precios[i];
    }
    for (int i = 0; i < M; i++) {
        cin >> v >> w;
        g.ponArista(v - 1, w - 1);
    }
    Personajes p(g, precios);

    cout << p.res() << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    // Resolvemos
    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
