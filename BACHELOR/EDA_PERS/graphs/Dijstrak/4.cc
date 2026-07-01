#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> Row;
typedef vector<pair<int,int>> Pars;
typedef vector<Pars> Mat;

void djs(const Mat& mappa, Row& dist, Row& ways, int in, int fi) {
    int node, size, adj, rec, pes;
    priority_queue <pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Sup;
    Sup.push(make_pair(0,in));
    dist[in] = 0;
    ways[in] = 1;
    while (!Sup.empty()) {
        rec = Sup.top().first;
        node = Sup.top().second;
        Sup.pop();
        if (rec == dist[node]) {
        if (node == fi) return;

        size = mappa[node].size();
        for (int i = 0; i < size; ++i) {
            adj = mappa[node][i].first;
            pes = mappa[node][i].second;
            if (dist[adj] == -1 or (dist[adj] != -1 and rec+pes < dist[adj])) {
                ways[adj] = ways[node];
                dist[adj] = rec+pes;
                Sup.push(make_pair(dist[adj],adj));
            }
            else if (rec+pes == dist[adj]) ways[adj] += ways[node];
        }
    }
    }
}

int main() {
    int vert, art, k1, k2, pes;
    while (cin >> vert >> art) {
        Row dist(vert, -1);
        Row ways(vert, 0);
        Mat mappa(vert);
        for (int i = 0; i < art; ++i) {
            cin >> k1 >> k2 >> pes;
            mappa[k1].push_back(make_pair(k2,pes));
        }
        cin >> k1 >> k2;
        djs(mappa, dist, ways, k1, k2);
        if (dist[k2] != -1) cout << "cost " << dist[k2] << ", " << ways[k2] << " way(s)"; 
        else cout << "no path from " << k1 << " to " << k2;
        cout << endl;
    }
}
