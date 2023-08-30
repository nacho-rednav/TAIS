/*
 * MUY IMPORTANTE: Solo se corregirán los comentarios y el código
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificación fuera de esas etiquetas no será corregida.
 */

/*@ <answer>
 *
 * Indicad el nombre completo y usuario del juez de quienes habéis hecho esta solución:
 * Estudiante 1: VICTOR ORTEGO MARTIN TAIS72
 * Estudiante 2: NACHO REDONDO NAVARRO TAIS85
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <memory>
#include <stdexcept>
#include <queue>
using namespace std;


/*@ <answer>
 
 Para solucionar el ejercicio representamos cada poblacion como un vertice y cada carretera como
 una arista de un grafo valorado. La solución consiste en descubrir el árbol de recubrimiento mínimo
 mediante el algoritmo de kruskal de cada componente conexa del grafo. El único cambio respecto a la implementación original es que no se añadirá
 una arista si su coste es mayor o igual que el del aeropuerto, por lo que puede haber más de un ARM dentro de una misma componente conexa.
 Cada ARM representa un aeropuerto que se va a construir. El número de ARM será el número de conjuntos del ConjuntoDisjunto del algoritmo de kruskal.
 El coste final será el coste total caminos + coste aeropuerto * número de aeropuertos
 
 Coste: O(max(V, AlogA)), expliación en la función "kruskal" de la clase Aeropuerto
 @ </answer> */

// ================================================================
// Escribe el código completo de tu solución aquí debajo (después de la marca)
//@ <answer>


template <typename Valor>
class Arista {
public:
    Arista() : pimpl(nullptr) {}
    Arista(int v, int w, Valor valor) : pimpl(std::make_shared<Arista_impl>(v, w, valor)) {}

    int uno() const { return pimpl->v; }
    int otro(int u) const { return (u == pimpl->v) ? pimpl->w : pimpl->v; }
    Valor valor() const { return pimpl->valor; }

    void print(std::ostream& o = std::cout) const {
        o << "(" << pimpl->v << ", " << pimpl->w << ", " << pimpl->valor << ")";
    }

    bool operator<(Arista<Valor> const& b) const {
        return valor() < b.valor();
    }
    bool operator>(Arista<Valor> const& b) const {
        return b.valor() < valor();
    }
private:
    struct Arista_impl {
        int v, w;
        Valor valor;
        Arista_impl(int v, int w, Valor valor) : v(v), w(w), valor(valor) {}
    };

    std::shared_ptr<Arista_impl> pimpl; // puntero a la arista "de verdad"
};

template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, Arista<Valor> const& ar) {
    ar.print(o);
    return o;
}


template <typename Valor>
using AdysVal = std::vector<Arista<Valor>>;  // lista de adyacentes a un vértice

template <typename Valor>
class GrafoValorado {
public:

    /**
     * Crea un grafo valorado con V vértices, sin aristas.
     */
    GrafoValorado(int V) : _V(V), _A(0), _ady(_V) { }

    /**
     * Crea un grafo valorado a partir de los datos en el flujo de entrada (si puede).
     * primer es el índice del primer vértice del grafo en el entrada.
     */
    GrafoValorado(std::istream& flujo, int primer = 0) : _A(0) {
        flujo >> _V;
        if (!flujo) return;
        _ady.resize(_V);
        int E, v, w;
        Valor c;
        flujo >> E;
        while (E--) {
            flujo >> v >> w >> c;
            ponArista({ v - primer, w - primer, c });
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
     * Añade una arista al grafo.
     * @throws invalid_argument si algún vértice no existe
     */
    void ponArista(Arista<Valor> arista) {
        int v = arista.uno(), w = arista.otro(v);
        if (v < 0 || v >= _V || w < 0 || w >= _V)
            throw std::invalid_argument("Vertice inexistente");
        ++_A;
        _ady[v].push_back(arista);
        _ady[w].push_back(arista);
    }

    /**
     * Devuelve la lista de adyacentes de v.
     * @throws invalid_argument si v no existe
     */
    AdysVal<Valor> const& ady(int v) const {
        if (v < 0 || v >= _V)
            throw std::invalid_argument("Vertice inexistente");
        return _ady[v];
    }

    /**
     * Devuelve las aristas del grafo.
     */
    std::vector<Arista<Valor>> aristas() const {
        std::vector<Arista<Valor>> ars;
        for (int v = 0; v < V(); ++v)
            for (auto arista : ady(v))
                if (v < arista.otro(v))
                    ars.push_back(arista);
        return ars;
    }

    /**
     * Muestra el grafo en el stream de salida o
     */
    void print(std::ostream& o = std::cout) const {
        o << _V << " vértices, " << _A << " aristas\n";
        for (auto v = 0; v < _V; ++v) {
            o << v << ": ";
            for (auto const& w : _ady[v]) {
                o << w << " ";
            }
            o << "\n";
        }
    }

private:
    int _V;   // número de vértices
    int _A;   // número de aristas
    std::vector<AdysVal<Valor>> _ady;   // vector de listas de adyacentes
};


/**
 * Para mostrar grafos por la salida estándar.
 */

template <typename Valor>
inline std::ostream& operator<<(std::ostream& o, GrafoValorado<Valor> const& g) {
    g.print(o);
    return o;
}


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


class Aeropuertos {
public:
    Aeropuertos(const GrafoValorado<int>&g, int coste):coste_aeropuerto(coste), coste_camino(0), num_aeropuertos(0) {
        kruskal(g);
    }
    int coste_total() { return coste_camino + num_aeropuertos * coste_aeropuerto; }
    int get_aeropuertos() { return num_aeropuertos; }

private:
    int coste_camino, num_aeropuertos, coste_aeropuerto;

    void kruskal(const GrafoValorado<int>& g) {//O(max(V, AlogA)) Puede darse el caso de que AlogA < V, si A=0 por ejemplo
        priority_queue<Arista<int>, vector<Arista<int>>, greater<Arista<int>>>pq;
        for (auto a : g.aristas()) {//O(A)
            pq.push(a);
        }
        ConjuntosDisjuntos c(g.V()); //O(V) 
        int v, w;

        while (!pq.empty()) { //O(A)
            auto a = pq.top(); pq.pop();//O(logA) costes cola de prioridad
            v = a.uno(); w = a.otro(v);
            if (!c.unidos(v, w)) { //O(1) Costes ConjuntoDisjunto
                if (a.valor() < coste_aeropuerto) {
                    c.unir(v, w);//(1) Costes ConjuntoDisjunto
                    coste_camino += a.valor();
                }
            }
        }
        num_aeropuertos = c.num_cjtos();
    }

};



bool resuelveCaso() {
  
  // leemos la entrada
  int N, M, A, v, w, val;
  cin >> N >> M >> A;
  if (!cin)
    return false;
  GrafoValorado<int> g(N);
  
  for (int i = 0; i < M; i++) {
      cin >> v >> w >> val;
      g.ponArista({ v - 1, w - 1, val });
  }
  // leer el resto del caso y resolverlo
  Aeropuertos ar(g, A);
  
  cout << ar.coste_total() << " " << ar.get_aeropuertos() << "\n";
  
  
  return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta línea ya no forma parte de la solución.

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
 // system("PAUSE");
#endif
  return 0;
}
