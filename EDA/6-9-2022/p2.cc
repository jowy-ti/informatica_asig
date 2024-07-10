#include <iostream>
#include <queue>
using namespace std;


int main() {
  queue<int> cua;
  int x;
  while (cin >> x) cua.push(x);

  cout << "nombre elements: " << cua.size() << endl;

  while (not cua.empty()) {
    cout << ' ' << cua.front();
    cua.pop();
  }
  cout << endl;
}
