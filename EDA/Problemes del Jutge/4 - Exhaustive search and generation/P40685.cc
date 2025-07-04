// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
#include <map>
using namespace std;

typedef vector <string>VS;
typedef vector <int>VI;
typedef list <int>LI;
typedef vector <LI>VLI;

VI v;
LI sol;

void print() {
	bool first = true;
	cout << "{";
	for (int i : sol) {
		if (first) first = false;
		else cout << ",";
		cout << i;
	}
	cout << "}" << endl;
}

void backtracking(int s, int i, int saux) {
	if (i == v.size() and saux == s) print();
	if (i < v.size()) {
		sol.push_back(v[i]);
		backtracking(s, i+1, saux+v[i]);
		sol.pop_back();
		backtracking(s, i+1, saux);
	}
}

int main() {
	int s, n;
	cin >> s >> n;
	v = VI(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	sort(v.begin(), v.end());
	backtracking(s, 0, 0);
}
