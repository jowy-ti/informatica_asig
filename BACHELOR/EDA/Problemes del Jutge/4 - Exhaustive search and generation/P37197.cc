// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
#include <map>
using namespace std;

typedef map <char, int>MI;
typedef vector <bool>VB;
typedef vector <char>VC;
typedef vector <VB>VVB;

MI conv;
VC v;
VVB mat;
VB done;

void backtracking(string sol, int ant) {
	if (sol.length() == v.size()) cout << sol << endl;
	else {
		for (int i = 0; i < mat.size(); i++) {
			if (!done[i] and mat[ant][i]) {
				done[i] = true;
				backtracking(sol+v[i], i);
				done[i] = false;
			}
		}
	}
}

int main() {
	int n, m;
	cin >> n;
	v = VC(n);
	for (int i = 0; i < n; i++) {
		cin >> v[i];
		conv[v[i]] = i;
	}
	cin >> m;
	mat = VVB(n, VB(n, true));
	for (int i = 0; i < m; i++) {
		char a, b;
		cin >> a >> b;
		int na = conv[a];
		int nb = conv[b];
		mat[nb][na] = mat[na][nb] = false;
	}
	done = VB(n, false);
	for (int i = 0; i < n; i++) {
		string sol = "";
		sol += v[i];
		done[i] = true;
		backtracking(sol, i);
		done[i] = false;
	}
}
