// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <set>
using namespace std;

int main() {
	set <string> s;
	set <string>::iterator it = s.begin(), mid;
	string w;
	cin >> w;
	if (w != "END") {
		it = s.insert(it, w);
		cout << w << endl;
		mid = s.begin();
		while (cin >> w and w != "END") {
			s.insert(it, w);
			if (w < *mid and s.size() % 2 == 0) --mid;
			else if (w > *mid and s.size() % 2 != 0) ++mid;
			cout << *mid << endl;
		}
	}
}
