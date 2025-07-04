#include<iostream>
#include<cmath>
using namespace std;

void comb(int num1, int num2, int cont, int pos, int& cont1) {
    int cop2 = num2;
    int sum = 0;

    if (cont < pos) {
        cout << cont << endl;
        for (int i = 0; i < num1; ++i) {
            if (num1-i == cop2) {
                sum += pow(2,num1-i-1);
                cont -= pow(2,num1-i-1);
                --cop2;
                cout << "1";
            }
            else if (pow(2,num1-i-2) <= cont) {
                int sumcop = 0;
                for (int j = 0; j < cop2; ++j) sumcop += pow(2,num1-j-i-2);
                if (sumcop <= cont) {
                    cout << "1";
                    sum += pow(2,num1-i-1);
                    cont -= pow(2,num1-i-1);
                    --cop2;
                }
                else cout << "0";
            }
            else cout << "0";
            if (i+1 < num1) cout << " ";
        }
        cout << endl;
        ++cont1;
        comb(num1, num2, sum, pos, cont1);
    }
    return;
}

int main() {
    int num1, num2;
    int pos = 0;
    int cont = 0;
    int cont1 = 0;
    cin >> num1 >> num2;
    for (int i = 0; i < num2; ++i) cont += pow(2,i);
    for (int i = 0; i < num2; ++i) pos += pow(2,num1-i-1);
    cont -= 1;
    comb(num1, num2, cont, pos, cont1);
}
