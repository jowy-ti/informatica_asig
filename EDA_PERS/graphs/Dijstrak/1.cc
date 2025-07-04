#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> Row;
typedef vector<pair<int,int>> Pars;
typedef vector<Pars> Mat;

void djs(const Mat& mappa, Row& dist, int in, int fi) {
    int node, size, adj, rec, pes;
    priority_queue <pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Sup;
    Sup.push(make_pair(in,0));
    dist[in] = 0;
    while (!Sup.empty()) {
        node = Sup.top().first;
        rec = Sup.top().second;
        Sup.pop();

        size = mappa[node].size();
        for (int i = 0; i < size; ++i) {
            adj = mappa[node][i].first;
            pes = mappa[node][i].second;
            if (dist[adj] >= 0) {
                if (rec+pes < dist[adj]) {
                    dist[adj] = rec+pes;
                    Sup.push(make_pair(adj,dist[adj]));
                }
            }
            else {
                dist[adj] = rec+pes;
                Sup.push(make_pair(adj,dist[adj]));
            }
        }
    }
    if (dist[fi] != -1) cout << dist[fi] << endl;
    else cout << "no path from " << in << " to " << fi << endl;
}

int main() {
    int vert, art, k1, k2, pes;
    while (cin >> vert >> art) {
        Row dist(vert, -1);
        Mat mappa(vert);
        for (int i = 0; i < art; ++i) {
            cin >> k1 >> k2 >> pes;
            mappa[k1].push_back(make_pair(k2,pes));
        }
        cin >> k1 >> k2;
        djs(mappa, dist, k1, k2);
    }
}
