#include <iostream>
#include <vector>
using namespace std;

bool dic(double x, const vector<double>& v, int l, int r) {
    int m = (r+l)/2;
    if (l == r) return v[m] == x;
    if (l > r) return false;
    if (v[m] == x) return true;
    if (v[m+1] == x) return true;
    
    if (x > v[m] and x > v[m+1]) return dic(x, v, m+1, r);
    if (x < v[m] and x < v[m+1]) return dic(x, v, l, m-1);
    if (r-l >= 2) {
        if (x > v[m-1]) return dic(x, v, m+1, r);
        if (x < v[m-1]) return dic(x, v, l, m-1);
        else return true;
    }
    return false;
}

bool resistant_search(double x, const vector<double>& v) {
    return dic(x, v, 0, v.size()-1);
}

int main() {
    double x;
    vector<double> v(8);
    cin >> x;
    for (int i = 0; i < 8; ++i) {
        cin >> v[i];
    }
    if (resistant_search(x, v)) cout << "found" << endl;
    else cout << "not found" << endl;
}
