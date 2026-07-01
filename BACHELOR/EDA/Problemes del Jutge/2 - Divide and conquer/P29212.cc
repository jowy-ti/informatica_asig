// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
using namespace std;

int exp_rapida_mod(int n, int k, int m) {
	if (k == 0) return 1;
	else {
		int y = exp_rapida_mod(n, k / 2, m);
		if (k % 2 == 0) return (y * y) % m;
		else return ((y * n) % m * y) % m;
	}
}

int main() {
	int n, k, m;
	while (cin >> n >> k >> m) cout << exp_rapida_mod(n, k, m) << endl;
}
