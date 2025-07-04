// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
using namespace std;

void dfs_rec(const vector <vector <char> >& G, int x, int y, vector <vector <bool> >& vis, int& count) {
	if (not vis[x][y]) {
		vis[x][y] = true;
		if (G[x][y] == 't') ++count;
		if (G[x][y] != 'X') {
			if (y != G[0].size()-1) dfs_rec(G, x, y+1, vis, count);
			if (x != G.size()-1) dfs_rec(G, x+1, y, vis, count);
			if (y != 0) dfs_rec(G, x, y-1, vis, count);
			if (x != 0) dfs_rec(G, x-1, y, vis, count);
		}
	}
}

int main() {
	int n, m;
	cin >> n >> m;

	vector <vector <char> > graf(n, vector <char>(m));

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> graf[i][j];
		}
	}

	int x, y;
	cin >> x >> y;
	vector <vector <bool> > visited(n, vector <bool>(m, false));
	int count = 0;
	dfs_rec(graf, x-1, y-1, visited, count);

	cout << count << endl;
}
