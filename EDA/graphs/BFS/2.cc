#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<char> Row;
typedef vector<Row> Mat;
typedef vector<vector<bool>> Matbool;
typedef pair<int,int> Cord;
typedef pair<Cord,int> Val;

void bfs(const Mat& tab, int x, int y, int midv, int midh, queue<Val>& cola, int& max, Matbool& visit) {
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
        if (tab[x][y] == 't') max = cont;
        cola.pop();
        if (y+1 < midh and tab[x][y+1] != 'X' and !visit[x][y+1]) {
            visit[x][y+1] = true;
            par.first.second = y+1;
            par.first.first = x;
            par.second = cont+1;
            cola.push(par);
        }
        if (y-1 >= 0 and tab[x][y-1] != 'X' and !visit[x][y-1]) {
            visit[x][y-1] = true;
            par.first.second = y-1;
            par.first.first = x;
            par.second = cont+1;
            cola.push(par);
        }
        if (x+1 < midv and tab[x+1][y] != 'X' and !visit[x+1][y]) {
            visit[x+1][y] = true;
            par.first.first = x+1;
            par.first.second = y;
            par.second = cont+1;
            cola.push(par);
        }
        if (x-1 >= 0 and tab[x-1][y] != 'X' and !visit[x-1][y]) {
            visit[x-1][y] = true;
            par.first.first = x-1;
            par.first.second = y;
            par.second = cont+1;
            cola.push(par);
        }
    }
}

int main() {
    int midv, midh, x, y;
    int max = -1;
    cin >> midv >> midh;
    Mat tab(midv,Row(midh));
    Matbool visit(midv, vector<bool>(midh, false));
    queue<Val> cola;
    
    for (int i = 0; i < midv; ++i) {
        for (int j = 0; j < midh; ++j) {
            cin >> tab[i][j];
        }
    }
    cin >> x >> y;
    visit[x-1][y-1] == true;
    bfs(tab, x-1, y-1, midv, midh, cola, max, visit);
    if (max != -1) cout << "maximum distance: " << max << endl;
    else cout << "no treasure can be reached" << endl;
}
