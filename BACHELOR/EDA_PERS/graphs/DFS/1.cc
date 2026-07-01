#include <iostream>
#include <vector>
using namespace std;

typedef vector<char> Row;
typedef vector<Row> Mat;

void founded(int n, int m, int r, int c, Mat& t, bool& find) {
    if (t[r][c] == 't') find = true;
    else t[r][c] = 'X';
    
    if (r-1 >= 0 and t[r-1][c] != 'X' and !find) {
        founded(n, m, r-1, c, t, find);
    }
    if (c+1 < m and t[r][c+1] != 'X' and !find) {
        founded(n, m, r, c+1, t, find);
    }
    if (r+1 < n and t[r+1][c] != 'X' and !find) {
        founded(n, m, r+1, c, t, find);
    }
    if (c-1 >= 0 and t[r][c-1] != 'X' and !find) {
        founded(n, m, r, c-1, t, find);
    }
}

int main() {
    int n, m, r, c;
    bool find = false;
    cin >> n >> m;
    Mat t(n,Row(m));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            cin >> t[i][j];
        }
    }
    cin >> r >> c;
    founded(n, m, r-1, c-1, t, find);
    if (find) cout << "yes" << endl;
    else cout << "no" << endl;
}
