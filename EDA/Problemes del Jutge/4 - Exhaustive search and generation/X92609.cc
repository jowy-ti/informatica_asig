// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector <int>VI;
typedef vector <bool>VB;

VB c1, c2;
VI v;

int backtrack_rec(int x, int n, int sum, int i) {
	if (sum == x) return 1;
	else if (x > sum and i < n) {
		int tot = 0;
		if (v[i]+sum <= x) {
			if (!c1[i]) {
				c1[i] = true;
				tot += backtrack_rec(x, n, sum+v[i], i);
				c1[i] = false;
			} else if (!c2[i]) {
				c2[i] = true;
				tot += backtrack_rec(x, n, sum+v[i], i+1);
				c2[i] = false;
			}
			tot += backtrack_rec(x, n, sum, i+1);
		}

		return tot;
	}
	return 0;
}

void backtrack(int x, int n) {
	sort(v.begin(), v.end());
	c1 = VB(n, false);
	c2 = VB(n, false);
	cout << backtrack_rec(x, n, 0, 0) << endl;
}

int main() {
	int x, n;
	while (cin >> x >> n) {
		v = VI(n);
		for (int i = 0; i < n; i++) {
			cin >> v[i];
		}
		backtrack(x, n);
	}
}
