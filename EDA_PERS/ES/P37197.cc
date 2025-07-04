#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef pair<char,int> Pars;
typedef vector<Pars> Row;
typedef vector<vector<bool>> Mat;

void esc(int n, Row& sol) {
    for (int i = 0; i < n; ++i) cout << sol[i].first;
    cout << endl;
}

bool vert(int i, int ind, int sp, const Mat& inc, Row& sol) {
    if (inc[sp][sol[ind-1].second]) return false;
    else return true;
}
 
void emp(int n, int ind, vector<char> spec, const Mat& inc, Row& sol, vector<bool>& vis) {
    if (ind == n) esc(n, sol);
    else {
        for (int i = 0; i < n; ++i) {
            if (!vis[i]) {
                if (ind == 0 or vert(i, ind, i, inc, sol)) {
                    vis[i] = true;
                    sol[ind].first = spec[i];
                    sol[ind].second = i;
                    emp(n, ind+1, spec, inc, sol, vis);
                    vis[i] = false;
                }
            }
        }
    }
}
 
int main () {
    int num_spec, num_inc;
    char k1, k2;
    int r1, r2;
    cin >> num_spec;
    Row sol(num_spec);
    vector<bool> vis(num_spec, false);
    vector<char> spec(num_spec);
    map<char,int> mappa;
    Mat inc(num_spec,vector<bool>(num_spec));
    for (int i = 0; i < num_spec; ++i) {
        cin >> spec[i];
        mappa.insert(make_pair(spec[i], i));
    }
    cin >> num_inc;
    for (int i = 0; i < num_inc; ++i) {
        cin >> k1 >> k2;
        r1 = mappa.find(k1)->second;
        r2 = mappa.find(k2)->second;
        inc[r1][r2] = true;
        inc[r2][r1] = true;
    }
    emp(num_spec, 0, spec, inc, sol, vis);
}
