// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
using namespace std;

bool es_doscol(const vector <vector <int> >& g, vector <int>& t, int u, int oldu) {
	if (t[u] == 0) {
		t[u] = t[oldu] % 2+1;
		for (int i : g[u]) {
			if (not es_doscol(g, t, i, u)) return false;
		}
		return true;
	} else return t[u] != t[oldu];
}

bool dfs(const vector <vector <int> >& adj) {
	vector <int> color(adj.size(), 0);
	for (int i = 0; i < adj.size(); ++i) {
		if (color[i] == 0 and not es_doscol(adj, color, i, i)) return 0;
	}
	return 1;
}

int main() {
	int n, m;
	while (cin >> n >> m) {
		int x, y;
		vector <vector <int> > adj(n);
		for (int i = 0; i < m; ++i) {
			cin >> x >> y;
			adj[x].push_back(y);
			adj[y].push_back(x);
		}

		cout << (dfs(adj) ? "yes" : "no") << endl;
	}
}
