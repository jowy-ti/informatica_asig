#include<iostream>
#include<vector>
#include<set>
using namespace std;

struct Pars{
    int val;
    char car;
    bool vert;
};
typedef pair<int,char> Dob;
typedef set<Pars> Bol;

void esc(int value, vector<Dob>& coin) {
    int size = coin.size();
    cout << value << " =";
    for (int i = 0; i < size; ++i) {
        if (coin[i].second == 'p') cout << " " << coin[i].first << 'p';
        else cout << " " << coin[i].first;
        if (i+1 != size) cout << " +";
    }
    cout << endl;
}

void coins(int value, int ind, int n, vector<Dob>& coin, Bol& coin_vis) {
    if (ind == value) esc(value, coin);
    else if (ind < value) {
        for (Bol::const_iterator it = coin_vis.begin(); it != coin_vis.end(); ++it) {
            if (!it->vert) {
                it->vert = true;
                coin.push_back(Dob(it->val, it->car));
                coins(value, ind+it->val, n, coin, coin_vis);
                it->vert = false;
            }
        }
    }
}

int main() {
    int value, n, num;
    while (cin >> value >> n)
    vector<Dob> coin;
    Bol coin_vis;
    for (int i = 0; i < num; ++i) {
        cin >> num;
        coin_vis.insert(Pars(num,'a',false));
        coin_vis.insert(Pars(num,'p',false));
    }
    coins(value, 0, n, coin, coin_vis);
    cout << "----------" << endl;
}
