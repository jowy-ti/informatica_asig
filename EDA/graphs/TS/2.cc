#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

typedef vector<string> Fil;
typedef map<string,Fil> Map;
typedef map<string,int> List;

void topsort(Map& adj, List& ref, int n, queue<string>& orden) {
    int size;
    List::iterator it1;
    Map::iterator it2;
    List::const_iterator it;
    priority_queue <string, vector<string>, greater<string>> Sup;
    
    for (it = ref.begin(); it != ref.end(); ++it) {
        if (it->second == 0) Sup.push(it->first);
    }
    
    while (!Sup.empty()) {
        string val = Sup.top();
        Sup.pop();
        orden.push(val);
        it2 = adj.find(val);
        size = it2->second.size();
        
        for (int i = 0; i < size; ++i) {
            it1 = ref.find(it2->second[i]);
            if (--it1->second == 0) Sup.push(it1->first);
        }
    }
}

void imp(Map& adj, List& ref, int n) {
    int size;
    queue<string> orden;
    topsort(adj, ref, n, orden);
    size = orden.size();
    if (size == n) {
        for (int i = 0; i < n; ++i) {
            cout << orden.front();
            orden.pop();
        }
    }
    else cout << "NO VALID ORDERING";
    cout << endl;
}

int main() {
    int n, m;
    string pal1, pal2;
    while (cin >> n) {
        Map adj;
        List ref;
        Fil abc;
        for (int i = 0; i < n; ++i) {
            cin >> pal1;
            ref.insert(make_pair(pal1,0));
            adj.insert(make_pair(pal1,abc));
        }
        cin >> m;
        List::iterator it1;
        Map::iterator it2;
        for (int i = 0; i < m; ++i) {
            cin >> pal1 >> pal2;
            it2 = adj.find(pal1);
            it2->second.push_back(pal2);
            it1 = ref.find(pal2);
            ++it1->second;
        }
        imp(adj, ref, n);
    }
}
