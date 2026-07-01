// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
using namespace std;

int n;
vector <int>v;
vector <bool>usat;

void escriu() {
	cout << '(';
	for (int i = 0; i < n; ++i) {
		cout << v[i];
		if (i != n-1) cout << ',';
	}

	cout << ')' << endl;
}

void write(int index) {
	if (index == n) return escriu();
	for (int i = 0; i < n; ++i) {
		if (not usat[i]) {
			usat[i] = true;
			v[index] = i+1;
			write(index+1);
			usat[i] = false;
		}
	}
}


int main() {
	cin >> n;
	v = vector <int>(n);
	for (int i = 0; i < n; ++i) v[i] = i+1;

	usat = vector <bool>(n, false);

	write(0);
}