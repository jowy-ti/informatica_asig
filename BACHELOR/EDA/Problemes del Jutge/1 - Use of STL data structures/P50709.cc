// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <queue>
using namespace std;

int main() {
	int n;
	char c;
	priority_queue <int> q;
	while (cin >> c) {
		if (c == 'S') {
			cin >> n;
			q.push(n);
		} else if (q.empty()) {
			if (c == 'I' or c == 'D') cin >> n;
			cout << "error!" << endl;
		} else if (c == 'A') cout << q.top() << endl;
		else if (c == 'R') q.pop();
		else {
			cin >> n;
			if (c == 'D') n = -n;
			n = q.top()+n;
			q.pop();
			q.push(n);
		}
	}
}
