#include <iostream>
#include <vector>
using namespace std;

int mod(int n, int k, int m) {
    if (k == 0)
        return 1;
    else {
        int y = mod(n, k/2, m);
        cout << y << " " << k << endl;
        int res = (y*y) % m;
        if (k%2 == 1) res = (n*res)%m;
        cout << res << endl;
        return res;
    }
}

int main() {
    int n, k, m;
    while (cin >> n >> k >> m) {
        cout << mod(n, k, m) << endl;
    }
}
