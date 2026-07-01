// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <map>
using namespace std;

int main() {
	string op;
	map <string, int> m;
	map <string, int>::iterator it;
	while (cin >> op) {
		if (op == "minimum?") {
			if (m.empty()) cout << "indefinite minimum" << endl;
			else {
				it = m.begin();
				cout << "minimum: " << it->first << ", " << it->second << " time(s)" << endl;
			}
		} else if (op == "maximum?") {
			if (m.empty()) cout << "indefinite maximum" << endl;
			else {
				it = --m.end();
				cout << "maximum: " << it->first << ", " << it->second << " time(s)" << endl;
			}
		} else if (op == "store") {
			cin >> op;
			it = m.find(op);
			if (it == m.end()) m.insert(make_pair(op, 1));
			else ++it->second;
		} else {
			cin >> op;
			it = m.find(op);
			if (it != m.end()) {
				--it->second;
				if (it->second == 0) m.erase(it);
			}
		}
	}
}
