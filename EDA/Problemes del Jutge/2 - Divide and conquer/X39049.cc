// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
using namespace std;

void producto(vector <int>& a, vector <int>& b) {
	vector <int>res(a.size());
	for (int i = 0; i < a.size(); ++i) {
		res[i] = a[b[i]];
	}
	a = res;
}

vector <int>fast_exponentiation(vector <int>& p, int k) {
	vector <int>res(p.size());
	if (k == 0) {
		for (int i = 0; i < p.size(); ++i) res[i] = i;
		return res;
	}

	res = fast_exponentiation(p, k / 2);
	if (k % 2 == 0) {
		producto(res, res);
	} else {
		producto(res, res);
		producto(res, p);
	}
	return res;
}

int main() {
	int n;
	while (cin >> n) {
		vector <int> perm(n);
		for (int i = 0; i < n; ++i) cin >> perm[i];

		int k; cin >> k;
		vector <int> res = fast_exponentiation(perm, k);
		for (int i = 0; i < n; ++i) {
			cout << res[i];
			if (i != n-1) cout << ' ';
		}
		cout << endl;
	}
}
