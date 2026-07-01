#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Mat;

void colore(vector<int>& visit, const Mat& graf, int ant, int i, bool& posb) {
    for (int j = 0; j < graf[i].size() and posb; ++j) {
        int val = graf[i][j];
        if (ant != val) {
            if (visit[i] == visit[val]) posb = false;
            else if (visit[val] == 0) {
                if (visit[i] == 1) visit[val] = 2;
                else visit[val] = 1;
                colore(visit, graf, i, val, posb);
            }
        }
    }
}

void evencycle(vector<int>& visit, const Mat& graf) {
    int size = graf.size();
    bool posb = true;
    for (int i = 0; i < size; ++i) {
        if (visit[i] == 0) {
            visit[i] = 1;
            colore(visit, graf, i, i, posb);
            if (!posb) {
                cout << "no" << endl;
                return;
            }
        }
    }
    cout << "yes" << endl;
}

int main() {
    int vert, arist, fil, col;
    while (cin >> vert >> arist) {
        Mat graf(vert);
        vector<int> visit(vert, 0);
        for (int i = 0; i < arist; ++i) {
            cin >> fil >> col;
            graf[fil].push_back(col);
            graf[col].push_back(fil);
        }
        evencycle(visit, graf);
    }
}
