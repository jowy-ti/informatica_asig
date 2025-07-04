// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
using namespace std;

void permuta(int i, vector <bool>& used_cons, vector <bool>& used_vows, vector <char>& cons, vector <char>& vows, vector <char>& sol) {
	int n = cons.size();
	if (i == n) {
		for (int i = 0; i < sol.size(); ++i) cout << sol[i];
		cout << endl;
	} else {
		for (int j = 0; j < n; ++j) {
			if (!used_cons[j]) {
				sol[2 * i] = cons[j];
				used_cons[j] = true;
				for (int k = 0; k < n; ++k) {
					if (!used_vows[k]) {
						used_vows[k] = true;
						sol[2 * i+1] = vows[k];
						permuta(i+1, used_cons, used_vows, cons, vows, sol);
						used_vows[k] = false;
					}
				}
				used_cons[j] = false;
			}
		}
	}
}

int main() {
	int n;
	cin >> n;
	vector <char>cons(n);
	for (int i = 0; i < n; ++i) cin >> cons[i];
	vector <char>vows(n);
	for (int i = 0; i < n; ++i) cin >> vows[i];

	vector <bool>used_cons(n, false);
	vector <bool>used_vows(n, false);
	vector <char>sol(n * 2);
	permuta(0, used_cons, used_vows, cons, vows, sol);
}
