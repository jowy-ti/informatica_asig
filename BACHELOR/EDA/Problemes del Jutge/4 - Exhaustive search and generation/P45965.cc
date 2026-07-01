// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
using namespace std;

void write(const vector <bool>& v) {
	bool first = true;
	for (int i = 0; i < v.size(); i++) {
		if (first) {
			first = false;
		} else {
			cout << " ";
		}
		cout << v[i];
	}
	cout << endl;
}


void write_in(vector <bool>& v, int i, int u, int z) {
	if (u+z == 0) write(v);
	else {
		if (z) {
			v[i] = false;
			write_in(v, i+1, u, z-1);
		}
		if (u) {
			v[i] = true;
			write_in(v, i+1, u-1, z);
		}
	}
}

void write(int n, int ones) {
	vector <bool>v(n);
	write_in(v, 0, ones, n-ones);
}


int main() {
	int ones, n;
	cin >> n >> ones;
	escriure(n, ones);
}
