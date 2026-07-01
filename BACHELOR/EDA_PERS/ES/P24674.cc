#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

void esc(const vector<string>& vec, int num) {
    cout << "(";
    for (int i = 0; i < num; ++i) {
        cout << vec[i];
        if (i+1 < num) cout << ",";
    }
    cout << ")" << endl;
}

void perm(vector<string>& vec, int num, int ind, vector<bool>& vis, const vector<string>& vec2) {
    if (ind == num) esc(vec, num);
    else {
        for (int i = 0; i < num; ++i) {
            if (vis[i] == false) {
                vis[i] = true;
                vec[ind] = vec2[i];
                perm(vec, num, ind+1, vis, vec2);
                vis[i] = false;
            }
        }
    }
}

int main() {
    int num;
    cin >> num;
    vector<string> vec(num);
    vector<string> vec2(num);
    vector<bool> vis(num, false);
    for (int i = 0; i < num; ++i) {
        cin >> vec[i];
        vec2[i] = vec[i];
    }
    perm(vec, num, 0, vis, vec2);
}
