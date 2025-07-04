#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<char> Row;
typedef vector<Row> Mat;
typedef pair<int,int> Cord;
typedef pair<Cord,int> Val;

void bfs(Mat& tab, int x, int y, int midv, int midh, queue<Val>& cola) {
    Val par;
    par.first.first = x;
    par.first.second = y;
    par.second = 0;
    cola.push(par);
    while (!cola.empty()) {
        par = cola.front();
        x = par.first.first;
        y = par.first.second;
        int cont = par.second;
        if (tab[x][y] == 't') return;
        cola.pop();
        tab[x][y] = 'X';
        if (y+1 < midh and tab[x][y+1] != 'X') {
            par.first.second = y+1;
            par.first.first = x;
            par.second = cont+1;
            cola.push(par);
        }
        if (y-1 >= 0 and tab[x][y-1] != 'X') {
            par.first.second = y-1;
            par.first.first = x;
            par.second = cont+1;
            cola.push(par);
        }
        if (x+1 < midv and tab[x+1][y] != 'X') {
            par.first.first = x+1;
            par.first.second = y;
            par.second = cont+1;
            cola.push(par);
        }
        if (x-1 >= 0 and tab[x-1][y] != 'X') {
            par.first.first = x-1;
            par.first.second = y;
            par.second = cont+1;
            cola.push(par);
        }
    }
}

int main() {
    int midv, midh, x, y;
    int cont = 0;
    cin >> midv >> midh;
    Mat tab(midv,Row(midh));
    queue<Val> cola;
    
    for (int i = 0; i < midv; ++i) {
        for (int j = 0; j < midh; ++j) {
            cin >> tab[i][j];
        }
    }
    cin >> x >> y;
    bfs(tab, x-1, y-1, midv, midh, cola);
    if (!cola.empty()) cout << "minimum distance: " << cola.front().second << endl;
    else cout << "no treasure can be reached" << endl;
}
