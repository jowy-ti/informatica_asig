// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

typedef pair <int, bool>P;
typedef vector <P>VP;
typedef vector <VP>VVP;
typedef vector <bool>VB;

VVP mat;
VB sol;
int m;
bool oneTime;

void checkl() {
	bool good = true;
	for (int i = 0; good and i < m; i++) {
		bool op = false;
		for (int j = 0; !op and j < 3; j++) {
			int num = mat[i][j].first;
			op = (mat[i][j].second and sol[num]) or (!mat[i][j].second and !sol[num]);
		}
		good = op;
	}
	if (good) {
		oneTime = true;
		bool first = true;
		for (int i = 0; i < sol.size(); i++) {
			if (first) first = false;
			else cout << " ";
			if (!sol[i]) cout << "-";
			cout << (char)('a'+i);
		}
		cout << endl;
	}
}

void backtracking(int i) {
	if (i == sol.size()) checkl();
	else {
		sol[i] = true;
		backtracking(i+1);
		sol[i] = false;
		backtracking(i+1);
	}
}

int main() {
	int n;
	cin >> n >> m;
	mat = VVP(m, VP(3));
	sol = VB(n);
	oneTime = false;
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 3; j++) {
			string aux;
			cin >> aux;
			if (aux[0] == '-') {
				mat[i][j].first = aux[1]-'a';
				mat[i][j].second = false;
			} else {
				mat[i][j].first = aux[0]-'a';
				mat[i][j].second = true;
			}
		}
	}
	backtracking(0);
	if (!oneTime) cout << "-" << endl;
}
