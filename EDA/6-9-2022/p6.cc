#include <iostream>
#include <set>
using namespace std;


int main() {
  set<int> S;
  int x;
  while (cin >> x) S.insert(x);

  cout << "nombre elements: " << S.size() << endl;

//  for (set<int>::iterator it = S.begin(); it != S.end(); ++it)
//    cout << ' ' << *it;

//  for (auto it = S.begin(); it != S.end(); ++it)
//    cout << ' ' << *it;

  for (int x : S) cout << ' ' << x;
  cout << endl;

  if (S.find(42) != S.end()) cout << "si" << endl;
  else cout << "no" << endl;

  S.erase(42);
}
