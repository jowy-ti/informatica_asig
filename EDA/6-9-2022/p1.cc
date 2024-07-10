#include <iostream>
#include <stack>
using namespace std;


int main() {
  stack<int> pila;
  int x;
  while (cin >> x) pila.push(x);

  cout << "nombre elements: " << pila.size() << endl;

  while (not pila.empty()) {
    cout << ' ' << pila.top();
    pila.pop();
  }
  cout << endl;
}
