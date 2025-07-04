// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <map>
using namespace std;

int main() {
	int x, y, n, pos;
	map <int, int> m;
	map <int, int>::iterator it;
	bool found = false;
	while (cin >> x >> y >> n) {
		pos = 1;
		m.insert(make_pair(n, 0));
		while (n <= 100000000 and not found) {
			if (n % 2 == 0) n = n / 2+x;
			else n = 3 * n+y;
			it = m.find(n);
			if (it == m.end()) m.insert(make_pair(n, pos));
			else {
				n = pos-(it->second);
				found = true;
			}
			++pos;
		}

		cout << n << endl;
		m.clear();
		found = false;
	}
}
