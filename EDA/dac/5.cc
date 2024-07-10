#include <iostream>
#include <vector>
using namespace std;

int dic(const vector<int> &v1, int x, int l, int r, int res) {
    if (l > r) return res;
    int m = (r+l)/2;
    if (v1[m]+x > m+1) return dic(v1, x, l, m-1, res);
    if (v1[m]+x < m+1) return dic(v1, x, m+1, r, res);
    return dic(v1, x, l, m-1, m+1);
}

int main () {
    int num1, num2;
    int cont = 1;
    vector<int> v1;
    vector<int> v2;
    while (cin >> num1) {
        vector<int> v1(num1);
        for (int i = 0; i < num1; ++i) {
            cin >> v1[i];
        }
        cin >> num2;
        vector<int> v2(num2);
        for (int i = 0; i < num2; ++i) {
            cin >> v2[i];
        }
        cout << "Sequence #" << cont << endl;
        for (int i = 0; i < num2; ++i) {
            int valor = dic(v1, v2[i], 0, v1.size()-1, -1);
            if (valor >= 0) cout << "fixed point for " << v2[i] << ": " << valor << endl;
            else cout << "no fixed point for " << v2[i] << endl;
        }
        ++cont;
        cout << endl;
    }
}
