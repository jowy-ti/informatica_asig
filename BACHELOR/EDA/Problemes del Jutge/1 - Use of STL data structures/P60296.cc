// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <algorithm>
#include <map>
#include <set>
using namespace std;


struct compare {
	bool operator() (const pair <string, int> &a, const pair <string, int> &b) const {
		if (a.second == b.second) return a.first < b.first;
		return a.second > b.second;
	}
};

int main() {
	map <string, pair <bool, int> > pl;
	map <string, pair <bool, int> >::iterator it, it2;

	string i, p;
	while (cin >> i >> p) {
		it = pl.find(p);
		if (i == "LOGIN") {
			if (it == pl.end()) pl.insert(make_pair(p, make_pair(true, 1200)));
			else it->second.first = true;
		} else if (i == "LOGOUT" and it != pl.end()) it->second.first = false;
		else if (i == "PLAY") {
			cin >> p;
			it2 = pl.find(p);
			if (it != pl.end() and it->second.first and it2 != pl.end() and it2->second.first) {
				it->second.second += 10;
				it2->second.second -= 10;
				if (it2->second.second < 1200) it2->second.second = 1200;
			} else cout << "jugador(s) no connectat(s)" << endl;
		} else if (i == "GET_ELO") {
			if (it != pl.end()) cout << p << ' ' << it->second.second << endl;
		}
	}
	cout << endl << "RANKING" << endl;

	set <pair <string, int>, compare>pls;
	for (pair <string, pair <bool, int> >p : pl) pls.insert(make_pair(p.first, p.second.second));
	for (pair <string, int>its : pls) cout << its.first << ' ' << its.second << endl;
}
