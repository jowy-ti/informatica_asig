// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
using namespace std;

typedef vector <bool>VB;
typedef vector <VB>VVB;

VB r, c;
VB d1, d2;

void printM(const VVB& mat) {
	for (int i = 0; i < mat.size(); i++) {
		for (int j = 0; j < mat.size(); j++) {
			cout << (mat[i][j] ? '.' : 'Q');
		}
		cout << endl;
	}
}

int queensin(VVB& rein, int i) {
	if (i == rein.size()) {
		printM(rein);
		return 1;
	}
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
			sol += queensin(rein, i+1);
			if (sol) return sol;
			rein[i][j] = true;
			r[i] = true;
			c[j] = true;
			d1[i+j] = true;
			d2[i-j+rein.size()] = true;
		}
	}
	return sol;
}


int reines(VVB& rein) {
	r = VB(rein.size(), true);
	c = VB(rein.size(), true);
	d1 = VB(rein.size() * 2-1, true);
	d2 = VB(rein.size() * 2-1, true);
	return queensin(rein, 0);
}

int main() {
	int n;
	cin >> n;
	VVB rein(n, VB(n, true));
	int sol = reines(rein);
	if (!sol) cout << "NO SOLUTION" << endl;
}
