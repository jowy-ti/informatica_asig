#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<int> Row;
typedef vector<pair<int,int>> Pars;
typedef vector<Pars> Mat;

void djs(const Mat& mappa, Pars& dist, Row& orden, int in, int fi) {
    int node, size, adj, rec, pes;
    priority_queue <pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> Sup;
    Sup.push(make_pair(in,0));
    dist[in].first = 0;
    dist[in].second = 0;
    while (!Sup.empty()) {
        node = Sup.top().first;
        rec = Sup.top().second;
        Sup.pop();

        size = mappa[node].size();
        for (int i = 0; i < size; ++i) {
            adj = mappa[node][i].first;
            pes = mappa[node][i].second;
            if (rec+pes < dist[adj].first) {
                if (dist[adj].first >= 0) {
                    dist[adj].first = rec+pes;
                    Sup.push(make_pair(adj,dist[adj].first));
                    orden[adj] = node;
                    dist[adj].second = dist[node].second+1;
                }
            }
            else if (dist[adj].first == -1) {
                dist[adj].first = rec+pes;
                Sup.push(make_pair(adj,dist[adj].first));
                orden[adj] = node;
                dist[adj].second = dist[node].second+1;
            }
            else if (rec+pes == dist[adj].first and dist[adj].second > dist[node].second+1) {
                dist[adj].second = dist[node].second+1;
            }
        }
    }
    if (dist[fi].first != -1) cout << "cost " << dist[fi].first << ", " << dist[fi].second << " step(s)";
    else cout << "no path from " << in << " to " << fi;
    cout << endl;
}

int main() {
    int vert, art, k1, k2, pes;
    while (cin >> vert >> art) {
        Row orden(vert, -1);
        Pars dist(vert, make_pair(-1,-1));
        Mat mappa(vert);
        for (int i = 0; i < art; ++i) {
            cin >> k1 >> k2 >> pes;
            mappa[k1].push_back(make_pair(k2,pes));
        }
        cin >> k1 >> k2;
        djs(mappa, dist, orden, k1, k2);
    }
}
