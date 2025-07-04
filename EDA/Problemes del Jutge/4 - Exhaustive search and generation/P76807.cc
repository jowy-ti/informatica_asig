// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
using namespace std;

typedef vector <vector <int> >grid;
typedef vector <vector <bool> >VVB;

class Sudoku {
grid G;
VVB rows;
VVB columns;
VVB boxes;
bool solved;

void write_solution() {
	solved = true;
	for (int i = 0; i < 9; ++i) {
		cout << G[i][0];
		for (int j = 1; j < 9; ++j)
			cout << " " << G[i][j];
		cout << endl;
	}
}

bool possible(int x, int y, int j) {
	return not rows[x][j-1] and not columns[y][j-1] and not boxes[(x / 3) * 3+(y / 3)][j-1] and not solved;
}

void solve(int i) {
	if (i == 81)
		write_solution();
	else {
		int x = i / 9;
		int y = i % 9;

		if (G[x][y] == -1) {
			for (int j = 1; j <= 9; ++j) {
				if (possible(x, y, j)) {
					G[x][y] = j;
					rows[x][j-1] = columns[y][j-1] = boxes[(x / 3) * 3+(y / 3)][j-1] = true;
					solve(i+1);
					G[x][y] = -1;
					rows[x][j-1] = columns[y][j-1] = boxes[(x / 3) * 3+(y / 3)][j-1] = false;
				}
			}
		} else
			solve(i+1);
	}
}

void read_grid() {
	char c;
	for (int i = 0; i < 9; ++i) {
		for (int j = 0; j < 9; ++j) {
			cin >> c;
			if (c == '.')
				G[i][j] = -1;
			else {
				int x = int(c-'0');
				G[i][j] = x;
				rows[i][x-1] = true;
				columns[j][x-1] = true;
				boxes[(i / 3) * 3+(j / 3)][x-1] = true;
			}
		}
	}
}

public:
Sudoku() {
	G = grid(9, vector <int>(9));
	rows = VVB(9, vector <bool>(9, false));
	columns = VVB(9, vector <bool>(9, false));
	boxes = VVB(9, vector <bool>(9, false));
	solved = false;

	read_grid();

	solve(0);
}
};

int main() {
	int n;
	cin >> n;
	cout << n << endl;
	for (int i = 0; i < n; ++i) {
		cout << endl;
		Sudoku s;
	}
}
