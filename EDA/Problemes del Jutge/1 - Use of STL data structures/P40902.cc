// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <map>
using namespace std;

int main() {
	string p, op;
	int c;
	map <string, int> m;
	map <string, int>::iterator it;
	while (cin >> p >> op) {
		it = m.find(p);
		if (op == "enters") {
			if (it == m.end()) m.insert(make_pair(p, 0));
			else cout << p << " is already in the casino" << endl;
		} else if (op == "wins") {
			cin >> c;
			if (it != m.end()) it->second += c;
			else cout << p << " is not in the casino" << endl;
		} else {
			if (it != m.end()) {
				cout << p << " has won " << it->second << endl;
				m.erase(it);
			} else cout << p << " is not in the casino" << endl;
		}
	}
	cout << "----------" << endl;
	it = m.begin();
	while (it != m.end()) {
		cout << it->first << " is winning " << it->second << endl;
		++it;
	}
}
