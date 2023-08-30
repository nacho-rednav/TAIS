/*
 * MUY IMPORTANTE: Solo se corregir�n los comentarios y el c�digo
 * contenidos entre las etiquetas <answer> y </answer>.
 * Toda modificaci�n fuera de esas etiquetas no ser� corregida.
 */

 /*@ <answer>
  *
  * Indicad el nombre completo y usuario del juez de quienes hab�is hecho esta soluci�n:
  * Estudiante 1: VICTOR ORTEGO MARTIN TAIS72
  * Estudiante 2: IGNACIO REDONDO NAVARRO TAIS85
  *
  *@ </answer> */

#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;


/*@ <answer>

El problema se resuelve por programaci�n din�mica siguiendo el hecho de que toda soluci�n que empiece
por los caracteres palabra1[i], palabra2[j] ser� mejor o igual que cualquier soluci�n que empiece
usando i+1, j+1 o ambos. Esto se debe a que los caracteres a partir de palabra1[i+1] est�n contenidos en
los que parten de palabra1[i], por lo que toda subsecuencia obtenido usando i+1 podr�a obtenerse usando i.
Lo mismo ocurre con j y palabra2.
Seguimos la siguiente recursi�n:
Vamos mirando las dos cadenas con los �nidces i y j.
Si palabra1[i] == palabra2[j] entonces ese car�cter se incluir� en la subsecuencia, por eso la longitud de la soluci�n
ser� lo que obtengamos mirando palabra1[i+1] y palabra2[j+1] + 1, que es el car�cter que acabamos de mirar
Si palabras[i] != palabras[j] entonces tenemos dos posibles opciones, comparar las cadenas que empiezan por palabra1[i+1] y palabra2[j]
o comparar las que empiezan por palabra1[i] y palabra2[j+1]. De esas dos nos quedamos con la mejor opci�n
Una vez construida la tabla se reconstruye la soluci�n. Para reconstruir se recorren las cadenas y si palabra1[i] == palabra2[j] se a�ade
el caracter a la soluci�n. Si no, se mira si lo que se hizo en la recursion fue aumentar i o aumentar j, se aumenta y se sigue comparando.

El coste en tiempo y en espacio es de O(X.length * Y.length) ya que se recorre toda la matriz, que es de ese tama�o, y si queremos
reconstruir la soluci�n no podemos ahorrar espacio con un vector

    subsecuencia(i,j) = subsecuencia con la longitud m�s larga obtenible con los caracteres a partir de palabra1[i] y palabra2[j]
    palabra1 y palabra2 son ambas secuencias de car�cteres que nos proporcionan en la entrada

    Casos Base:
        subsecuencia(i,j) = 0 i > X.length() or j > Y.length(), caso cadena vac�a
    Caso Recursivo:
        subsecuencia(i,j) = subsecuencia(i + 1, j + 1) + 1 si palabra1[i] == palabra2[j]
                          = max(subsecuencia(i + 1, j), subsecuencia(i, j + 1)) si palabra[i] != palabra[j]


 @ </answer> */

 // ================================================================
 // Escribe el c�digo completo de tu soluci�n aqu� debajo (despu�s de la marca)
 //@ <answer>


bool resuelveCaso() {

    // leemos la entrada
    string X, Y;
    cin >> X >> Y;

    if (!cin)
        return false;

    // resolver el caso
    vector<vector<int>> tabla(X.length() + 1, vector<int>(Y.length() + 1, 0));

    for (int i = X.length() - 1; i >= 0; i--) {
        for (int j = Y.length() - 1; j >= 0; j--) {
            if (X[i] == Y[j])
                tabla[i][j] = tabla[i + 1][j + 1] + 1;
            else
                tabla[i][j] = max(tabla[i + 1][j], tabla[i][j + 1]);
        }
    }

    int maxLong = tabla[0][0];
    string sol = "";

    int i = 0, j = 0;
    while (i < X.length() && j < Y.length()) {
        if (X[i] == Y[j]) {
            sol.push_back(X[i]); i++; j++;
        }
        else if (tabla[i][j] == tabla[i][j + 1]) {
            j++;
        }
        else if (tabla[i][j] == tabla[i + 1][j]) {
            i++;
        }
    }

    cout << sol << "\n";

    return true;
}

//@ </answer>
//  Lo que se escriba debajo de esta l�nea ya no forma parte de la soluci�n.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("sample.in");
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