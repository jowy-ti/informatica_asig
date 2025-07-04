#include<iostream>
#include<vector>
using namespace std;

typedef pair<char,bool> Pars;
typedef vector<Pars> Bol;

void cons_vow(int ind, int num, vector<char>& con, Bol& con2, vector<char>& vow, Bol& vow2) {
    if (ind == num*2) {
        for (int i = 0; i < num; ++i) cout << con[i] << vow[i];
        cout << endl;
    }
    else {
        for (int i = 0; i < num; ++i) {
            if (!con2[i].second and ind%2 == 0) {
                con2[i].second = true;
                con[ind/2] = con2[i].first;
                cons_vow(ind+1, num, con, con2, vow, vow2);
                con2[i].second = false;
            }
            if (!vow2[i].second and ind%2 != 0) {
                vow2[i].second = true;
                vow[ind/2] = vow2[i].first;
                cons_vow(ind+1, num, con, con2, vow, vow2);
                vow2[i].second = false;
            }
        }
    }
}

int main() {
    int num;
    cin >> num;
    vector<char> con(num);
    Bol con2(num);
    vector<char> vow(num);
    Bol vow2(num);
    for (int i = 0; i < num; ++i) {
        cin >> con2[i].first;
        con2[i].second = false;
    }
    for (int i = 0; i < num; ++i) {
        cin >> vow2[i].first;
        vow2[i].second = false;
    }
    cons_vow(0, num, con, con2, vow, vow2);
}
