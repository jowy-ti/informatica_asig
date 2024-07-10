#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<vector<string>> Mat;

void escribir(int p, const vector<string>& alf, const Mat& mapa) {
    int size;
    for (int i = 0; i < p; ++i) {
        cout << "subset " << i+1 << ": {";
        size = mapa[i].size();
        for (int j = 0; j < size; ++j) {
            cout << mapa[i][j];
            if (j+1 < size) cout << ",";
        }
        cout << "}" << endl;
    }
    cout << endl;
}

void sub(int ind, int p, const vector<string>& alf, Mat& mapa) {
    int n = alf.size();
    if (ind == n) escribir(p, alf, mapa);
    else {
        for (int i = 0; i < p; ++i) {
            mapa[i].push_back(alf[ind]);
            sub(ind+1, p, alf, mapa);
            mapa[i].pop_back();
        }
    }
}
 
int main () {
    int num, p;
    cin >> num;
    vector<string> alf(num);
    for (int i = 0; i < num; ++i) cin >> alf[i];
    cin >> p;
    Mat mapa(p);
    sub(0, p, alf, mapa);
}
