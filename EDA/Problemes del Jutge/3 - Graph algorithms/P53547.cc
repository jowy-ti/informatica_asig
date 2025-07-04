// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <string>
#include <queue>
#include <stdlib.h>
using namespace std;

struct cela {
	char type;
	char visited;
	int bishops;
	cela() : type('V'), visited(false), bishops(0) {
	}
};


typedef pair <int, int> pi;
typedef vector <cela> VC;
typedef vector <VC> MC;

int Alfil(MC &T, int i, int j) {
	queue <pi> q;
	q.push(pi(i, j));
	int x, y;
	int cells = 0;
	int bishops = 0;

	while (!q.empty()) {
		x = q.front().first;
		y = q.front().second;
		q.pop();
		if (T[x][y].type == 'V' and not T[x][y].visited) {
			T[x][y].visited = true;
			++cells;
			bishops += T[x][y].bishops;

			if (x+1 < T.size() and y+1 < T[0].size()) q.push(pi(x+1, y+1));
			if (x-1 >= 0 and y+1 < T[0].size()) q.push(pi(x-1, y+1));
			if (x+1 < T.size() and y-1 >= 0) q.push(pi(x+1, y-1));
			if (x-1 >= 0 and y-1 >= 0) q.push(pi(x-1, y-1));
		}
	}
	if (bishops % cells == 0) return bishops / cells;
	else return -2;
}

int main() {
	int n, m, k;
	string aux;

	cin >> k;
	for (int l = 0; l < k; ++l) {
		cin >> n >> m;
		MC taulell(n, VC(m));

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				cin >> aux;
				if (aux == "X") taulell[i][j].type = 'X';
				else taulell[i][j].bishops = atoi(aux.c_str());
			}
		}

		int mit_total = -1;
		int mit;

		for (int i = 0; i < n; ++i) {
			for (int j = 0; j < m; ++j) {
				if (taulell[i][j].type == 'V' and not taulell[i][j].visited) {
					mit = Alfil(taulell, i, j);
					if (mit_total == -1) mit_total = mit;
					else if (mit_total != mit) mit_total = -2;
				}
			}
		}

		cout << "Case " << (l+1) << ": ";
		if (mit_total == -2) cout << "no" << endl;
		else cout << "yes" << endl;
	}
}
