#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char>> Tab;

void esc(Tab& table, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << table[i][j];
        }
        cout << endl;
    }
}

void reines(int n, int ind, vector<bool>& col, vector<bool>& dia1, vector<bool>& dia2, Tab& table, bool& ver) {
    if (ind == n) {
        esc(table, n);
        ver = true;
    }
    else {
        for (int i = 0; i < n and ver == false; ++i) {
            int d1 = i-ind+n-1;
            int d2 = i+ind;
            if (!col[i] and !dia1[d1] and !dia2[d2]) {
                col[i] = true;
                dia1[d1] = true;
                dia2[d2] = true;
                table[ind][i] = 'Q';
                reines(n, ind+1, col, dia1, dia2, table, ver);
                table[ind][i] = '.';
                col[i] = false;
                dia1[d1] = false;
                dia2[d2] = false;
            }
        }
    }
}
int main() {
    int n;
    bool ver = false;
    cin >> n;
    Tab table(n,vector<char>(n,'.'));
    vector<bool> col(n, false);
    vector<bool> dia1(2*n-1, false);
    vector<bool> dia2(2*n-1, false);
    reines(n, 0, col, dia1, dia2, table, ver);
    if (!ver) cout << "NO SOLUTION" << endl;
}
