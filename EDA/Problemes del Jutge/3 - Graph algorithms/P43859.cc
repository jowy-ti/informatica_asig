// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef vector <pair <int, int> > VE;
typedef vector <VE> VVE;

int dijkstra(VVE& G, int source, int dest) {
	vector <bool>vis(G.size(), false);
	vector <int>dist(G.size(), 2147483647);
	priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > q;

	q.push({ 0, source });
	dist[source] = 0;

	while (!q.empty()) {
		int node = q.top().second;
		q.pop();

		if (!vis[node]) {
			vis[node] = true;
			for (pair <int, int>aux : G[node]) {
				int td = (dist[node]+aux.first);
				if (dist[aux.second] > td) {
					dist[aux.second] = td;
					q.push({ dist[aux.second], aux.second });
				}
			}
		}
	}
	return dist[dest];
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		int a, b, d;
		VVE adj(n);

		for (int i = 0; i < m; ++i) {
			cin >> a >> b >> d;
			adj[a].push_back(make_pair(d, b));
		}

		int x, y;
		cin >> x >> y;
		int res = dijkstra(adj, x, y);
		if (res != 2147483647) cout << res << endl;
		else cout << "no path from " << x << " to " << y << endl;
	}
}
