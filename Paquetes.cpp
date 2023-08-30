#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include "DigrafoValorado.h"
#include "IndexPQ.h"

const int INF = std::numeric_limits<int>::max();

class Dijkstra {
public:
    Dijkstra(DigrafoValorado<int> const& g, int orig) : origen(orig),
        dist(g.V(), INF), pq(g.V()) {
        dist[origen] = 0;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }

    int coste_camino(int d) {
        return dist[d];
    }
private:
    int origen;
    std::vector<int> dist;
    IndexPQ<int> pq;
    void relajar(AristaDirigida<int> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
        }
    }
};

bool tratar_caso() {
	int V, A, o, d, esf, O, P;
    int sum = 0;
    cin >> V >> A;
    if (!cin) return false;
    DigrafoValorado<int> g(V);
    for (int i = 0; i < A; i++) {
        cin >> o >> d >> esf;
        g.ponArista({ o - 1, d - 1, esf });
    }
    DigrafoValorado<int> gi = g.inverso();
    cin >> O >> P;
    O--;
    Dijkstra ida(g, O);
    Dijkstra vuelta(gi, O);
    vector<int>pedidos(P);
    for (int i = 0; i < P; i++) {
        cin >> pedidos[i];
    }
    int esf2 = 0;
    bool imp = false;
    for (int i = 0; i < P; i++) {
        d = pedidos[i] - 1;
        esf = ida.coste_camino(d);
        if (esf == INF) {
            imp = true; break;
        }
        esf2 = vuelta.coste_camino(d);
        if(esf2 == INF) {
            imp = true; break;
        }
        sum += (esf + esf2);
    }
    
    if (imp)cout << "Imposible\n";
    else cout << sum << "\n";
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