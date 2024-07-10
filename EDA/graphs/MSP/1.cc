#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int,int> Pars;
typedef vector<Pars> Row_Pars;
typedef vector<Row_Pars> Mat_Pars;

void search(const Mat_Pars& ind) {
    int node, pes, size, adj, pes_adj;
    int sum = 0;
    vector<bool> vis(ind.size(), false);
    priority_queue<Pars, Row_Pars, greater<Pars>> Sup;
    Sup.push(Pars(0,0));
    
    while (!Sup.empty()) {
        node = Sup.top().second;
        pes = Sup.top().first;
        Sup.pop();
        if (!vis[node]) {
            sum += pes;
            vis[node] = true;
            size = ind[node].size();
            for (int i = 0; i < size; ++i) {
                adj = ind[node][i].first;
                pes_adj = ind[node][i].second;
                Sup.push(Pars(pes_adj, adj));
            }
        }
    }
    cout << sum << endl;
}

int main() {
    int n,m,k1,k2,kg;
    while (cin >> n >> m) {
        Mat_Pars ind(n);
        for (int i = 0; i < m; ++i) {
            cin >> k1 >> k2 >> kg;
            ind[k1-1].push_back(Pars(k2-1,kg));
            ind[k2-1].push_back(Pars(k1-1,kg));
        }
        search(ind);
    }
}
