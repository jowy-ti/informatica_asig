// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

typedef vector <pair <int, int> >VE;
typedef vector <VE>VVE;

void dijkstra(VVE& G, int source, int dest) {
	int n = G.size();
	vector <bool> vis(n, false);
	vector <int> dist(n, 2147483647);
	vector <int> ways(n, 0);
	priority_queue <pair <int, int>, vector <pair <int, int> >, greater <pair <int, int> > > q;

	q.push({ 0, source });
	dist[source] = 0;
	ways[source] = 1;


	while (!q.empty()) {
		int node = q.top().second;
		q.pop();
		if (!vis[node]) {
			vis[node] = true;

			for (pair <int, int>aux : G[node]) {
				int td = (dist[node]+aux.first);
				if (dist[aux.second] > td) {
					ways[aux.second] = ways[node];
					dist[aux.second] = td;
					q.push({ dist[aux.second], aux.second });
				} else if (dist[aux.second] == td) ways[aux.second] += ways[node];
			}
		}
	}

	if (dist[dest] == 2147483647) {
		cout << "no path from " << source << " to " << dest << endl;
		return;
	}

	cout << "cost " << dist[dest] << ", " << ways[dest] << " way(s)" << endl;
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
		dijkstra(adj, x, y);
	}
}
