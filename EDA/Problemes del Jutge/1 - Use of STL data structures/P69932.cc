// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <set>
#include <sstream>
using namespace std;

int main() {
	string l;
	while (getline(cin, l)) {
		set <int> s;
		int i, c = 0;
		istringstream iss(l);
		while (iss >> i) s.insert(i);

		bool evodd;
		set <int>::iterator it = s.begin();
		while (it != s.end()) {
			if (it == s.begin()) {
				++c;
				evodd = (*it % 2 == 0);
			} else if (evodd and * it % 2 != 0) {
				++c;
				evodd = false;
			} else if (not evodd and * it % 2 == 0) {
				++c;
				evodd = true;
			}
			++it;
		}
		cout << c << endl;
	}
}
