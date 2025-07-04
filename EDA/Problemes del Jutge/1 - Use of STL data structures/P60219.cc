// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

struct compare {
	bool operator()(const string& a, const string& b) {
		if (a.length() == b.length()) return a < b;
		return a.length() < b.length();
	}
};

int main() {
	set <string> has;
	set <string, compare> had;
	string input;
	int game = 1;
	bool quit = 0, first = true;

	cin >> input;
	while (not quit) {
		while (not (input == "END" or input == "QUIT")) {
			if (has.count(input)) {
				has.erase(input);
				had.insert(input);
			} else {
				has.insert(input);
				had.erase(input);
			}
			cin >> input;
		}

		if (not first) cout << endl;
		first = false;

		cout << "GAME #" << game << endl << "HAS:" << endl;
		for (string elem : has) cout << elem << endl;
		cout << endl << "HAD:" << endl;
		for (string elem : had) cout << elem << endl;

		++game;
		has.erase(has.begin(), has.end());
		had.erase(had.begin(), had.end());

		if (input == "QUIT") quit = 1;
		else cin >> input;
	}
}
