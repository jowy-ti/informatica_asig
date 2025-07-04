#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

typedef pair<double,double> Cord;
typedef pair<Cord, double> Info;

void bfs(const vector<Info>& rock, vector<bool>& visit, queue<Cord>& cola, double dist) {
    int pos, desp;
    double x1 , y1, r1, x2, y2, r2, res;
    int size_rock = rock.size();
    Cord val(0,0);
    cola.push(val);
    
    while (!cola.empty()) {
        val = cola.front();
        pos = val.first;
        desp = val.second;
        if (pos == size_rock-1) return;
        cola.pop();
        x1 = rock[pos].first.first;
        y1 = rock[pos].first.second;
        r1 = rock[pos].second;
        for (int i = 0; i < size_rock; ++i) {
            if (!visit[i] and i != pos) {
                //cout << i << endl,
                x2 = rock[i].first.first;
                y2 = rock[i].first.second;
                r2 = rock[i].second;
                res = sqrt(pow(abs(x2-x1),2) + pow(abs(y2-y1),2)) - (r1+r2);
                if (res <= dist) {
                    //cout << x1 << " " << y1 << " " << r1 << " " << x2 << " " << y2 << " " << r2 << endl;
                    val.first = i;
                    val.second = desp+1;
                    cola.push(val);
                    visit[i] = true;
                }
            }
        }
    }
}

int main() {
    double num, dist;
    while (cin >> num >> dist) {
        vector<Info> rock(num);
        vector<bool> visit(num, false);
        queue<Cord> cola;
    
        for (int i = 0; i < num; ++i) cin >> rock[i].first.first >> rock[i].first.second >> rock[i].second;
        visit[0] = true;
        bfs(rock, visit, cola, dist);
        if (!cola.empty()) cout << cola.front().second << endl;
        else cout << "Xof!" << endl;
    }
}
