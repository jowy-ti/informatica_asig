// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector <int>VI;
typedef vector <bool>VB;

VB c1, c2;
VI v;

void print(int x, int n) {
	int sum = 0;
	cout << x << " = ";
	for (int i = 0; i < n; i++) {
		if (c1[i]) {
			cout << v[i];
			sum += v[i];
			if (sum != x) cout << " + ";
		}
		if (c2[i]) {
			cout << v[i] << "p";
			sum += v[i];
			if (sum != x) cout << " + ";
		}
	}
	cout << endl;
}

void backtracking_rec(int x, int n, int sum, int i) {
	if (sum == x) print(x, n);
	else if (x > sum and i < n) {
		if (v[i]+sum <= x) {
			if (!c1[i]) {
				c1[i] = true;
				backtracking_rec(x, n, sum+v[i], i);
				c1[i] = false;
			}
			if (!c2[i]) {
				c2[i] = true;
				backtracking_rec(x, n, sum+v[i], i+1);
				c2[i] = false;
			}
			backtracking_rec(x, n, sum, i+1);
		}
	}
}

void backtracking(int x, int n) {
	sort(v.begin(), v.end());
	c1 = VB(n, false);
	c2 = VB(n, false);
	backtracking_rec(x, n, 0, 0);
	cout << "----------" << endl;
}


int main() {
	int x, n;
	while (cin >> x >> n) {
		v = VI(n);
		for (int i = 0; i < n; i++) {
			cin >> v[i];
		}
		backtracking(x, n);
	}
}
