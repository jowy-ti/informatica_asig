// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector <char>VC;
typedef vector <VC>VVC;

typedef vector <bool>VB;
typedef vector <VB>VVB;

int bfs(VVC& mat, int i, int j) {
	VVB vis(mat.size(), VB(mat[0].size(), false));

	queue <pair <pair <int, int>, int> > q;
	q.push(make_pair(make_pair(i, j), 0));

	int x, y, d;
	while (!q.empty()) {
		x = (q.front().first).first;
		y = (q.front().first).second;
		d = q.front().second;
		q.pop();

		if (mat[x][y] == 't') return d;
		else if (!vis[x][y]) {
			vis[x][y] = true;
			if (x != 0 and mat[x-1][y] != 'X') q.push(make_pair(make_pair(x-1, y), d+1));
			if (x != mat.size()-1 and mat[x+1][y] != 'X') q.push(make_pair(make_pair(x+1, y), d+1));
			if (y != 0 and mat[x][y-1] != 'X') q.push(make_pair(make_pair(x, y-1), d+1));
			if (y != mat[0].size()-1 and mat[x][y+1] != 'X') q.push(make_pair(make_pair(x, y+1), d+1));
		}
	}
	return -1;
}

int main() {
	int n, m;

	cin >> n >> m;
	VVC mat(n, VC(m));
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			cin >> mat[i][j];
		}
	}

	int x, y;
	cin >> x >> y;
	int res = bfs(mat, x-1, y-1);
	if (res != -1) cout << "distancia minima: " << res << endl;
	else cout << "no es pot arribar a cap tresor" << endl;
}
