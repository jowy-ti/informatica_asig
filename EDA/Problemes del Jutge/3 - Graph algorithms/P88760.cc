// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <queue>
#include <math.h>

using namespace std;


struct roca {
	double x;
	double y;
	double r;
};

typedef pair <roca, int> Par;

bool can_jump(roca& orig, roca& dest, double d) {
	double x = (dest.x-orig.x) * (dest.x-orig.x);
	double y = (dest.y-orig.y) * (dest.y-orig.y);
	double dist = sqrt(x+y);
	dist = dist-orig.r-dest.r;
	return dist < d;
}

int bfs(vector <roca>& r, double d) {
	vector <bool>v(r.size(), false);
	queue <Par>q;
	q.push(Par(r[0], 0));
	vector <int>distancia(r.size(), -1);
	distancia[0] = 0;
	while (not q.empty()) {
		int index = q.front().second;
		roca ro = q.front().first;
		q.pop();
		if (not v[index]) {
			v[index] = true;
			for (int i = 0; i < r.size(); ++i) {
				if (can_jump(ro, r[i], d) and distancia[i] == -1) {
					q.push(Par(r[i], i));
					distancia[i] = distancia[index]+1;
					if (i == r.size()-1) return distancia[i];
				}
			}
		}
	}
	return -1;
}

int main() {
	int n;
	while (cin >> n) {
		double d;
		cin >> d;
		vector <roca> r(n);
		for (int i = 0; i < n; ++i) cin >> r[i].x >> r[i].y >> r[i].r;
		int dist = bfs(r, d);
		if (dist > 0) cout << dist << endl;
		else cout << "Xof!" << endl;
	}
}
