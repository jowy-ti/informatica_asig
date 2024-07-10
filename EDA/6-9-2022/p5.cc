#include <iostream>
#include <queue>
using namespace std;


int main() {
  priority_queue<int> cua;
  int x;
  while (cin >> x) cua.push(-x);

  cout << "nombre elements: " << cua.size() << endl;

  while (not cua.empty()) {
    cout << ' ' << -cua.top();
    cua.pop();
  }
  cout << endl;
}
