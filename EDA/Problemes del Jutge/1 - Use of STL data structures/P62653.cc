// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <queue>
using namespace std;

string tl;
struct Comp {
	bool operator()(const string& a, const string& b) {
		if (a.length() == b.length()) {
			string ctl = tl.substr(0, a.length());
			if (a == ctl) return 0;
			if (b == ctl) return 1;
			if (a < b) {
				if (a < ctl and ctl < b) return 1;
				return 0;
			} else {
				if (b < ctl and ctl < a) return 0;
				return 1;
			}
		} else return a.length() > b.length();
	}
};

int main() {
	while (cin >> tl) {
		char op;
		string sc;
		int tc = 0;
		priority_queue <string, vector <string>, Comp>sq;
		while (cin >> op and op != 'E') {
			if (op == 'S') {
				cin >> sc;
				sq.push(sc);
			} else tc += 1;

			while (tc > 0 and not sq.empty()) {
				cout << sq.top() << endl;
				sq.pop();
				--tc;
			}
		}

		cout << tc << " ticket(s) left" << endl;
		cout << sq.size() << " supporter(s) with no ticket" << endl << endl;
	}
}
