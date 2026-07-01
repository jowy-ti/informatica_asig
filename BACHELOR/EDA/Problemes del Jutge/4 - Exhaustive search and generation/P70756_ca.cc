// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
using namespace std;

void escribe(vector <vector <string> >& part) {
	int size = part.size();
	for (int i = 0; i < part.size(); ++i) {
		cout << "subconjunt " << i+1 << ": {";
		int size0 = part[i].size();
		for (int j = 0; j < size0-1; ++j) cout << part[i][j] << ",";
		if (not part[i].empty()) cout << part[i][size0-1];
		cout << "}" << endl;
	}
}

void fCombina(int x, vector <string>& vs,
	      vector <vector <string> >& part) {
	if (x == vs.size()) {
		escribe(part);
		cout << endl;
	} else {
		for (int i = 0; i < part.size(); ++i) {
			part[i].push_back(vs[x]);
			fCombina(x+1, vs, part);
			part[i].pop_back();
		}
	}
}

void combina(int x, int p, vector <string>& vs) {
	vector <vector <string> >part(p, vector <string> ());
	fCombina(x, vs, part);
}

int main() {
	int n;
	cin >> n;

	vector <string>vs(n);
	for (int i = 0; i < n; ++i) cin >> vs[i];

	int p;
	cin >> p;

	combina(0, p, vs);
}
