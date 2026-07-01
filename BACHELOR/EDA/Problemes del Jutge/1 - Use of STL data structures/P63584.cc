// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <map>
using namespace std;

typedef vector <int> VE;
typedef vector <VE> VVE;

int k_esim(int k, const VVE& V) {
	map <int, int>min;
	for (int i = 0; i < V.size(); i++) {
		if (not V[i].empty()) min[ V[i][0] ] = i;
	}

	pair <int, int>res;
	VE it(V.size(), 1);
	while (k--) {
		res = *min.begin();
		if (V[res.second].size() > it[res.second]) min[ V[res.second][it[res.second]++] ] = res.second;
		min.erase(min.begin());
	}
	return res.first;
}

/*
int main() {
    int x, y, k;
    cin >> x >> y;
    VVE v(x, VE(y));
    for (int i = 0; i < x; ++i) {
        for (int j = 0; j < y; ++j) cin >> v[i][j];
    }
    cin >> k;
    cout << k_esim(k, v) << endl;
}
*/
