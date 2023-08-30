#include <iostream>
#include <fstream>
using namespace std;
#include <vector>
#include <algorithm>


/*
La soluci�n se alcanza con un algoritmo voraz cuya estrategia consiste
en emparejar el usuario m�s pesado restante con el m�s ligero restante y si
no es posible el m�s pesado va s�lo.
Una pareja es factible (puede ir juntos) si la suma de sus pesos es menor o igual
que el l�mite

Dem:
Supongamos una soluci�n �ptima Y y la soluci�n voraz X
Las soluciones son conjuntos de pares que representan las parejas formadas.
Si alguien va s�lo se representa como si fuese emparejado con un usuario
de peso 0, representado por O.

En todo par la primera componente ser� el m�ximo del par y se ordena la 
soluci�n en orden descendente de la primera componente
Pares X (ai, bj) Pares Y(ci, dj)

Al encontrar la primera diferencia:
- Si ai != ci -> ci < ai Por como elige el voraz la soluci�n
	- Si bj == dj se puede cambiar ci por ai y como ci < ai la pareja anterior de ai sigue siendo v�lida con ci
	- Si dj == O se puede introducir la pareja (ai, bj) en Y, juntar a la pareja anterior de ai con ci (ci < ai) y dejar a la pareja anterior de bj sola en Y y que la solucion Y siga siendo factible sin haber aumentando el numero de parejas
	- Si bj == O se puede dejar ai solo en Y y juntar a la pareja anterior de ai con ci porque ci < ai
	- Si bj != dj != O:
		- Es imposbile que ocurra ai != ci AND bj != dj != O ya que al estar ordenados en orden descendente por primera componente todo lo posterior en Y va a ser
		menor o igual que ci, entonces ai no aparecer�a en la soluci�n Y
		- Por lo que bj != dj != O ocurrir� siendo ai == ci y adem�s sabemos que bj < dj por c�mo elige el voraz la soluci�n.
		Podemos intercambir bj por dj. La pareja (ci, bj) ser� factible (== (ai, bj)). Adem�s la pareja anterior de bj seguro ser� menor o igual que ci, ya que aparece m�s tarde en Y, por lo que puede juntarse con dj


*/

int resuelve(const vector<int>& v, int P) {
	int i = 0, j = v.size() - 1, res = 0;

	while (i < j) {
		if (v[i] + v[j] <= P) {
			i++; j--;
		}
		else if (v[i] + v[j] > P) {
			j--;
		}
		res++;
	}
	if (i == j) res++;

	return res;
}

bool tratar_caso() {
	int P, N;
	cin >> P >> N;
	if (!cin)return false;
	vector<int> v(N);
	for (int i = 0; i < N; i++) {
		cin >> v[i];
	}
	sort(v.begin(), v.end());
	cout << resuelve(v, P) << "\n";
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