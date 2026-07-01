// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector <int>VI;
typedef vector <bool>VB;

VI v;
VB sol;
bool trobat;

bool comp(int a, int b) {
	return a > b;
}

void print() {
	bool first = true;
	cout << "{";
	for (int i = 0; i < sol.size(); i++) {
		if (sol[i]) {
			if (first) first = false;
			else cout << ",";
			cout << v[i];
		}
	}
	cout << "}" << endl;
	trobat = true;
}

void backtracking(int s, int i, int saux) {
	if (!trobat) {
		if (i == v.size() and saux == s) print();
		else if (i < v.size()) {
			sol[i] = true;
			backtracking(s, i+1, saux+v[i]);
			if (!trobat) {
				sol[i] = false;
				backtracking(s, i+1, saux);
			}
		}
	}
}

int main() {
	int s, n;
	trobat = false;
	cin >> s >> n;
	v = VI(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	sol = VB(n, false);
	sort(v.begin(), v.end(), comp);
	backtracking(s, 0, 0);
	if (!trobat) {
		cout << "no solution" << endl;
	}
}
