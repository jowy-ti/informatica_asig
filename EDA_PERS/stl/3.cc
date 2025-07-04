#include<iostream>
#include<map>
using namespace std;

void collatz (int x, int y, int n, map<int,int>& cyc, int& cont) {
    map<int,int>::iterator it = cyc.find(n);
    
    if (it == cyc.end()) {
        cyc.insert(make_pair(n, 1));
        if (n%2 == 0) collatz (x, y, n/2+x, cyc, cont);
        else collatz (x, y, 3*n+y, cyc, cont);
    }
    else if (it->second == 1) {
        cyc[n] = 2;
        ++cont;
        if (n%2 == 0) collatz (x, y, n/2+x, cyc, cont);
        else collatz (x, y, 3*n+y, cyc, cont);
    }
}

int main() {
    map<int,int> cyc;
    int x, y, n;
    int cont = 0;
    cin >> x >> y >> n;
    collatz(x, y, n, cyc,cont);
    cout << cont << endl;
}
