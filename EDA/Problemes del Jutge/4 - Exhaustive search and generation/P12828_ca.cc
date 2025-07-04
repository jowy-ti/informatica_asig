// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
using namespace std;

void zu(vector <int>v, int n) {
	if (v.size() == n) {
		for (int i = 0; i < n; ++i) {
			cout << v[i];
			if (i != n-1) cout << ' ';
		}
		cout << endl;
	} else {
		v[n] = 0;
		zu(v, n+1);

		v[n] = 1;
		zu(v, n+1);
	}
}

int main() {
	int x;
	cin >> x;

	vector <int>v(x);
	zu(v, 0);
}