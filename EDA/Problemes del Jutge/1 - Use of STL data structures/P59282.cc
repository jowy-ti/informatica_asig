// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <map>
using namespace std;

int main() {
	cout.setf(ios::fixed);
	cout.precision(4);
	string s;
	int avgt = 0, avgd = 0;
	map <int, int> m;
	map <int, int>::iterator it;
	while (cin >> s) {
		if (s == "number") {
			int n;
			cin >> n;
			it = m.find(n);
			if (it != m.end()) ++it->second;
			else m.insert(make_pair(n, 1));
			++avgd;
			avgt += n;
		} else if (m.begin() != m.end()) {
			--avgd;
			avgt -= m.begin()->first;
			--m.begin()->second;
			if (m.begin()->second == 0) m.erase(m.begin());
		}
		if (m.size() == 0) cout << "no elements" << endl;
		else cout << "minimum: " << m.begin()->first << ", maximum: " << (--m.end())->first << ", average: " << avgt / double(avgd) << endl;
	}
}
