// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <queue>
#include <list>
using namespace std;

void pinta(vector <vector <char> >& mat, vector <vector <bool> >& vis, int i, int j) {
	char caracter = ' ';
	queue <pair <int, int> > q;
	list <pair <int, int> > a_pintar;
	q.push(make_pair(i, j));
	int x, y;
	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second;
		q.pop();
		if (!vis[x][y]) {
			vis[x][y] = true;
			if (mat[x][y] != '.') caracter = mat[x][y];
			else a_pintar.push_back(make_pair(x, y));

			if (x != 0 and mat[x-1][y] != '#') q.push(make_pair(x-1, y));
			if (x != mat.size()-1 and mat[x+1][y] != '#') q.push(make_pair(x+1, y));
			if (y != 0 and mat[x][y-1] != '#') q.push(make_pair(x, y-1));
			if (y != mat[0].size()-1 and mat[x][y+1] != '#') q.push(make_pair(x, y+1));
		}
	}

	if (caracter != ' ') for (pair <int, int> pos : a_pintar) mat[pos.first][pos.second] = caracter;
}

int main() {
	int n, m;

	while (cin >> n >> m) {
		vector <vector <char> > mat(n, vector <char>(m));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) cin >> mat[i][j];
		}

		vector <vector <bool> > vis(n, vector <bool>(m, false));
		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (not vis[i][j] and mat[i][j] != '#') pinta(mat, vis, i, j);
			}
		}

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) cout << mat[i][j];
			cout << endl;
		}
		cout << endl;
	}
}
