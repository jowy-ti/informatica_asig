#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<int>> Mat;

void cycle(vector<bool>& visit, const Mat& graf, int i, int ant, bool& posb) {
    visit[i] = true;
    for (int j = 0; j < graf[i].size(); ++j) {
        int val = graf[i][j];
        if (ant != val) {
            if (visit[val] == false) cycle(visit, graf, val, i, posb);
            else if (visit[val] == true) {
                posb = true;
                return;
            }
        }
    }
}
void numcycle(vector<bool>& visit,const Mat& graf, int& cont) {
    int size = graf.size();
    for (int i = 0; i < size; ++i) {
        if (!visit[i]) {
            bool posb = false;
            cycle(visit, graf, i, i, posb);
            if (posb) {
                cout << "no" << endl;
                return;
            }
            else ++cont;
        }
    }
    cout << cont << endl;
}

int main() {
    int vert, arist, fil, col;
    while (cin >> vert >> arist) {
        int cont = 0;
        Mat graf(vert);
        vector<bool> visit(vert, false);
        for (int i = 0; i < arist; ++i) {
            cin >> fil >> col;
            graf[fil].push_back(col);
            graf[col].push_back(fil);
        }
        numcycle(visit, graf, cont);
    }
}
