// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <map>
#include <list>
#include <queue>

using namespace std;

void ordenacio_topologica(map <string, int> &num, map <int, string> &str, vector <vector <int> > &graf, vector <int> &apuntat) {
	priority_queue <string, vector <string>, greater <string> > cola;
	map <string, int>::const_iterator it = num.begin();
	while (it != num.end()) {
		if (apuntat[it->second] == 0) {
			cola.push(it->first);
		}
		++it;
	}

	queue <string> cola_aux;
	while (not cola.empty()) {
		string u = cola.top();
		cola.pop();
		cola_aux.push(u);
		for (int v : graf[num[u]]) {
			if (--apuntat[v] == 0) {
				cola.push(str[v]);
			}
		}
	}

	int n = graf.size();
	if (cola_aux.size() != n) {
		cout << "NO VALID ORDERING" << endl;
	} else   {
		while (not cola_aux.empty()) {
			cout << cola_aux.front();
			cola_aux.pop();
		}
		cout << endl;
	}
}

int main() {
	int n;
	while (cin >> n) {
		map <string, int> num;
		map <int, string> str;
		for (int i = 0; i < n; i++) {
			string entrada;
			cin >> entrada;
			num.insert(make_pair(entrada, i));
			str.insert(make_pair(i, entrada));
		}

		int m;
		cin >> m;
		vector <int> apuntat(n, 0);
		vector <vector <int> > graf(n);
		for (int i = 0; i < m; i++) {
			string u, v;
			cin >> u >> v;
			graf[num[u]].push_back(num[v]);
			apuntat[num[v]]++;
		}

		ordenacio_topologica(num, str, graf, apuntat);
	}
}
