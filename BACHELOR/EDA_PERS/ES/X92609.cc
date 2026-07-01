#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void escribir(vector<int> &solucion, int tope, int x) {
    cout << x << " =";
    for (int i = 0; i < tope; i++) {
        if (solucion[i] != 0) {
            if (i%2 != 0) cout << " " << solucion[i] << 'p';
            else cout << " " << solucion[i];
            if (i+1 != tope) cout << " +";
        }
    }
    cout << endl;
}

void moneda(int i, int valor, int x, vector<int> &numeros, vector<int> &solucion, int& cont) {
    int n = numeros.size();
    if (valor == x) escribir(solucion, i, x);
    else if (i < n and valor < x) {
        for (int j = 0; j < 2; ++j) {
            if (j == 0) {
                solucion[i] = numeros[i];
                valor += numeros[i];
            }
            else if (j == 1) {
                solucion[i] = numeros[i];
                valor += numeros[i]*2;
            }
            moneda(i + 1, valor, x, numeros, solucion, cont);
            valor -= solucion[i];
            solucion[i] = 0;
        }
    }
}
 
int main () {
    int x, n;
    while (cin >> x >> n) {
        int cont = 0;
        vector<int> numeros(n, 0);
        for (int i = 0; i < n; i++) cin >> numeros[i];
        sort(numeros.begin(), numeros.end());
        vector<int> solucion(n);
        moneda(0, 0, x, numeros, solucion, cont);
        cout << cont << endl;
    }
}
