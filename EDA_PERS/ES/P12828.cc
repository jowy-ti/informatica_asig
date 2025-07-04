#include<iostream>
#include<cmath>
using namespace std;

void comb(int num, int cont) {
    if (cont < pow(2,num)) {
        int prob = cont;
        for (int i = 0; i < num; ++i) {
            int var = pow(2,num-i-1);
            if (var > prob) cout << "0";
            else {
                prob -= var;
                cout << "1";
            }
            if (i+1 < num) cout << " ";
        }
        cout << endl;
        comb(num, ++cont);
    }
}

int main() {
    int num;
    cin >> num;
    comb(num, 0);
}
