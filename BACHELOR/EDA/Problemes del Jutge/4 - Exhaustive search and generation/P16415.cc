// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
using namespace std;

typedef vector <bool>VB;
typedef vector <VB>VVB;

VB r, c;
VB d1, d2;

int queens_in(VVB& rein, int i) {
	if (i == rein.size()) return 1;
	bool first = true;
	int sol = 0;
	for (int j = 0; j < rein.size(); j++) {
		first = false;
		if (rein[i][j] and r[i] and c[j] and d1[i+j] and d2[i-j+rein.size()]) {
			rein[i][j] = false;
			r[i] = false;
			c[j] = false;
			d1[i+j] = false;
			d2[i-j+rein.size()] = false;
			sol += queens_in(rein, i+1);
			rein[i][j] = true;
			r[i] = true;
			c[j] = true;
			d1[i+j] = true;
			d2[i-j+rein.size()] = true;
		}
	}
	return sol;
}

int queens(VVB& rein) {
	r = VB(rein.size(), true);
	c = VB(rein.size(), true);
	d1 = VB(rein.size() * 2-1, true);
	d2 = VB(rein.size() * 2-1, true);
	return queens_in(rein, 0);
}


int main() {
	int n;
	cin >> n;
	VVB rein(n, VB(n, true));
	cout << queens(rein) << endl;
}
