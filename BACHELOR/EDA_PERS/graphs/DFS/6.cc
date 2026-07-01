#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char>> Mat;

void dfs(Mat& graf, int i, int j) {
    int size_fil = graf.size();
    int size_col = graf[0].size();
    int i_next = i+1;
    int i_ant = i-1;
    int j_next = j+1;
    int j_ant = j-1;
    
    if (i_next < size_fil and graf[i_next][j] == '.') {
        graf[i_next][j] = graf[i][j];
        dfs(graf, i_next, j);
    }
    if (i_ant >= 0 and graf[i_ant][j] == '.') {
        graf[i_ant][j] = graf[i][j];
        dfs(graf, i_ant, j);
    }
    if (j_ant >= 0 and graf[i][j_ant] == '.') {
        graf[i][j_ant] = graf[i][j];
        dfs(graf, i, j_ant);
    }
    if (j_next < size_col and graf[i][j_next] == '.') {
        graf[i][j_next] = graf[i][j];
        dfs(graf, i, j_next);
    }
}

void paint(Mat& graf) {
    int size_fil = graf.size();
    int size_col = graf[0].size();
    for (int i = 0; i < size_fil; ++i) {
        for (int j = 0; j < size_col; ++j) {
            if (graf[i][j] != '#' and graf[i][j] != '.') dfs(graf, i, j);
        }
    }
    for (int i = 0; i < size_fil; ++i) {
        for (int j = 0; j < size_col; ++j) {
            cout << graf[i][j];
        }
        cout << endl;
    }
}

int main() {
    int fil, col;
    while (cin >> fil >> col) {
        Mat graf(fil, vector<char>(col));
        for (int i = 0; i < fil; ++i) {
            for (int j = 0; j < col; ++j) {
                cin >> graf[i][j];
            }
        }
        paint(graf);
        cout << endl;
    }
}
