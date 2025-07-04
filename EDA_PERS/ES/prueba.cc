#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
 
void moneda(int i, int valor, int x, vector<int> &numeros, vector<int> &solucion, int& cont) {
    int n = numeros.size();
    if (valor == x) ++cont;
    else if (i < 2*n) {
        if (valor < x) {
            if ((i%2 != 0 and solucion[i-1] != 0) or i%2 == 0) {
                solucion[i] = numeros[i/2];
                valor += numeros[i/2];
                moneda(i + 1, valor, x, numeros, solucion, cont);
                valor -= numeros[i/2];
                solucion[i] = 0;
            }
            moneda(i + 1, valor, x, numeros, solucion, cont);
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
        vector<int> solucion(2*n);
        moneda(0, 0, x, numeros, solucion, cont);
        cout << cont << endl;
    }
}
