#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef vector<vector<int>> Mat;

void topsort(const Mat& adj, int n, queue<int>& orden) {
    int size;
    vector<int> ref(n,0);
    for (int i = 0; i < n; ++i) {
        size = adj[i].size();
        for (int j = 0; j < size; ++j) {
            ++ref[adj[i][j]];
        }
    }
    priority_queue <int, vector<int>, greater<int> > Sup;
    for (int i = 0; i < n; ++i) {
        if (ref[i] == 0) Sup.push(i);
    }
    
    while (!Sup.empty()) {
        int val = Sup.top();
        Sup.pop();
        size = adj[val].size();
        orden.push(val);
        
        for (int i = 0; i < size; ++i) {
            if (--ref[adj[val][i]] == 0) Sup.push(adj[val][i]);
        }
    }
}

void imp(const Mat& adj, int n) {
    
    queue<int> orden;
    topsort(adj, n, orden);
    for (int i = 0; i < n; ++i) {
        cout << orden.front();
        orden.pop();
        if (i+1 < n) cout << " ";
    }
}

int main() {
    int n, m, num1, num2;
    while (cin >> n >> m) {
        Mat adj(n);
        for (int i = 0; i < m; ++i) {
            cin >> num1 >> num2;
            adj[num1].push_back(num2);
        }
        imp(adj, n);
        cout << endl;
    }
}
