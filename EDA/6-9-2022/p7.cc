#include <iostream>
#include <map>
using namespace std;


int main() {
  map<string, int> M;
  string s, t;
  while (cin >> s >> t) {
    if (t == "enters") {
      if (M.find(s) != M.end())
        cout << t << " is already in the casino" << endl;
      else M[s] = 0;
    }
    else if (t == "wins")  {
      int x;
      cin >> x;
      auto it = M.find(s);
      if (it == M.end())
        cout << t << " is not in the casino" << endl;
      else it-> second += x;
//      else M[s] += x;
    }
    // ...
  }

  for (auto p : M) cout << p.first << " is winning " << p.second << endl;
}
