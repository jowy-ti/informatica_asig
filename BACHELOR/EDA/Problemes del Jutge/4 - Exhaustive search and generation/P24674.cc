// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
using namespace std;

void write(const vector <string>& v, const vector <int>& nv) {
	cout << "(";
	bool first = true;
	for (int i : nv) {
		if (first) {
			first = false;
		} else {
			cout << ",";
		}
		cout << v[i];
	}
	cout << ")" << endl;
}

void permute_in(const vector <string>& v, vector <int>& nv, int i, vector <bool>& used) {
	if (i == v.size()) write(v, nv);
	else {
		for (int k = 0; k < v.size(); k++) {
			if (!used[k]) {
				used[k] = true;
				nv[i] = k;
				permute_in(v, nv, i+1, used);
				used[k] = false;
			}
		}
	}
}


void permute(const vector <string>& v) {
	vector <bool>used(v.size(), false);
	vector <int>vn(v.size());
	permute_in(v, vn, 0, used);
}

int main() {
	int n;
	cin >> n;
	vector <string>v(n);
	for (int i = 0; i < n; i++) cin >> v[i];
	permute(v);
}
