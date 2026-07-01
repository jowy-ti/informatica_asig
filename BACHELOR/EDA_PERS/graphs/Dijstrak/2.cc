#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

typedef vector<int> Row;
typedef vector<pair<int,int>> Pars;
typedef vector<Pars> Mat;

void djs(const Mat& mappa, Row& dist, Row& orden, int in, int fi) {
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
                    orden[adj] = node;
                }
            }
            else {
                dist[adj] = rec+pes;
                Sup.push(make_pair(adj,dist[adj]));
                orden[adj] = node;
            }
        }
    }
    if (dist[fi] != -1) {
        stack<int> pila;
        node = fi;
        pila.push(node);
        while (node != in) {
            node = orden[node];
            pila.push(node);
        }
        while (!pila.empty()) {
            cout << pila.top();
            pila.pop();
            if (!pila.empty()) cout << " ";
        }
    }
    else cout << "no path from " << in << " to " << fi;
    cout << endl;
}

int main() {
    int vert, art, k1, k2, pes;
    while (cin >> vert >> art) {
        Row orden(vert, -1);
        Row dist(vert, -1);
        Mat mappa(vert);
        for (int i = 0; i < art; ++i) {
            cin >> k1 >> k2 >> pes;
            mappa[k1].push_back(make_pair(k2,pes));
        }
        cin >> k1 >> k2;
        djs(mappa, dist, orden, k1, k2);
    }
}
