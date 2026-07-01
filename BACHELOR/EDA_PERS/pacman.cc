#include<iostream>
#include<vector>
#include<queue>
using namespace std;

typedef pair<int,int> Pars;
typedef queue<Pars> Q_pars;
typedef vector<vector<bool>> Bol;
typedef vector<char> Row;
typedef vector<Row> Mat_char;

void cubrimiento(int numf, int numc, int i, int j, Bol& vis) {
    if (i+1 < numf) vis[i+1][j] = true;
    
    if (i-1 >= 0) vis[i-1][j] = true;
    
    if (j+1 < numc) {
        vis[i][j+1] = true;
        if (i-1 >= 0) vis[i-1][j+1] = true;
        if (i+1 < numf) vis[i+1][j+1] = true;
    }
    if (j-1 >= 0) {
        vis[i][j-1] = true;
        if (i-1 >= 0) vis[i-1][j-1] = true;
        if (i+1 < numf) vis[i+1][j-1] = true;
    }
}

bool bfs(Pars orig, int numf, int numc, const Mat_char& mapa, Bol& vis) {
    int i, j;
    Q_pars sup;
    sup.push(orig);
    if (vis[orig.first][orig.second]) return false;
    vis[orig.first][orig.second] = true;
    
    while (!sup.empty()) {
        i = sup.front().first;
        j = sup.front().second;
        sup.pop();
        if (mapa[i][j] == 'B') return true;
        
        if (i-1 >= 0 and mapa[i-1][j] != 'X' and !vis[i-1][j]) {
            vis[i-1][j] = true;
            sup.push(Pars(i-1,j));
        }
            
        if (i+1 < numf and mapa[i+1][j] != 'X' and !vis[i+1][j]) {
            vis[i+1][j] = true;
            sup.push(Pars(i+1,j));
        }
                
        if (j+1 < numc and mapa[i][j+1] != 'X' and !vis[i][j+1]) {
            vis[i][j+1] = true;
            sup.push(Pars(i,j+1));
        }
                    
        if (j-1 >= 0 and mapa[i][j-1] != 'X' and !vis[i][j-1]) {
            vis[i][j-1] = true;
            sup.push(Pars(i,j-1));
        }
    }
    return false;
}

int main() {
    int numf, numc;
    Pars orig;
    while (cin >> numf >> numc) {
        Mat_char mapa(numf,Row(numc));
        Bol vis(numf,vector<bool>(numc, false));
        for (int i = 0; i < numf; ++i)  {
            for (int j = 0; j < numc; ++j) {
                cin >> mapa[i][j];
                if (mapa[i][j] == 'P') orig = Pars(i,j);
                if (mapa[i][j] == 'F') cubrimiento(numf, numc, i, j, vis);
            }
        }
        if (bfs(orig, numf, numc, mapa, vis)) cout << "yes" << endl;
        else cout << "no" << endl;
    }
}
