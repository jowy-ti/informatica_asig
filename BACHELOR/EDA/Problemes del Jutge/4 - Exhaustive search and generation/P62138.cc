// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <algorithm>
#include <list>
#include <set>
using namespace std;

typedef vector <int>VI;
typedef list <int>LI;
typedef set <int>SI;
typedef vector <LI>LLI;
typedef vector <bool>VB;

LLI ll;
VI v;
LI sol;
SI seg;

void print() {
	bool first = true;
	for (int i : sol) {
		if (first) first = false;
		else cout << " ";
		cout << i;
	}
	cout << endl;
}

void backtracking_rec(int n) {
	if (!n) print();
	else {
		for (auto it = seg.begin(); it != seg.end(); it++) {
			int num = *it;
			for (int j : ll[num]) {
				if (!(--v[j])) seg.insert(j);
			}
			seg.erase(it);
			sol.push_back(num);
			backtracking_rec(n-1);
			sol.pop_back();
			auto aux = seg.insert(num);
			it = aux.first;
			for (int j : ll[num]) {
				if (!v[j]++) seg.erase(j);
			}
		}
	}
}

void backtracking() {
	int n = ll.size();
	for (int i = 0; i < n; i++) {
		if (!v[i]) seg.insert(i);
	}
	backtracking_rec(n);
}

int main() {
	int n, m;
	cin >> n >> m;
	ll = LLI(n);
	v = VI(n, 0);
	for (int i = 0; i < m; i++) {
		int x, y;
		cin >> x >> y;
		ll[x].push_back(y);
		v[y]++;
	}
	backtracking();
}
