// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

typedef pair <int, int> P;
typedef vector <P> VP;
typedef vector <VP> VVP;

int mst(const vector <vector <P> > & g) {
	int n = g.size();
	vector <bool>vis(n, false);
	vis[0] = true;
	priority_queue <P, vector <P>, greater <P> >q;

	for (P elem : g[0]) q.push(elem);
	int sz = 1;
	int sum = 0;

	while (sz < n) {
		int node = q.top().second;
		int dist = q.top().first;
		q.pop();

		if (!vis[node]) {
			vis[node] = true;
			for (P elem : g[node]) q.push(elem);
			sum += dist;
			++sz;
		}
	}
	return sum;
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		int a, b, d;
		VVP adj(n);

		for (int i = 0; i < m; ++i) {
			cin >> a >> b >> d;
			adj[a-1].push_back(make_pair(d, b-1));
			adj[b-1].push_back(make_pair(d, a-1));
		}

		int res = mst(adj);
		cout << res << endl;
	}
}
