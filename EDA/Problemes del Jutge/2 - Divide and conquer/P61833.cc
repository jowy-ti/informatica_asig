// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>

using namespace std;

typedef vector <vector <int> > matrix;

void mult(const matrix& M1, const matrix& M2, matrix& p, int m) {
	p = matrix(M1.size(), vector <int>(M2[0].size(), 0));
	for (int i = 0; i < M1.size(); ++i) {
		for (int j = 0; j < M2[0].size(); ++j) {
			for (int k = 0; k < M2.size(); ++k)
				p[i][j] += M1[i][k] * M2[k][j];
			p[i][j] %= m;
		}
	}
}

void powMatrix(const matrix& M, int n, int m, matrix& p) {
	if (n == 0) {
		p[0][0] = p[1][1] = 1;
		p[0][1] = p[1][0] = 0;
	} else if (n == 1) {
		p[0][0] = M[0][0] % m;
		p[0][1] = M[0][1] % m;
		p[1][0] = M[1][0] % m;
		p[1][1] = M[1][1] % m;
	} else if (n % 2 == 0) {
		matrix aux(2, vector <int>(2));
		powMatrix(M, n / 2, m, aux);
		mult(aux, aux, p, m);
	} else {
		matrix aux(2, vector <int>(2));
		powMatrix(M, n-1, m, aux);
		mult(M, aux, p, m);
	}
}

int main() {
	matrix m(2, vector <int>(2));
	int n, mod;
	while (cin >> m[0][0] >> m[0][1] >> m[1][0] >> m[1][1] >> n >> mod) {
		matrix p(2, vector <int>(2));
		powMatrix(m, n, mod, p);
		cout << p[0][0] << ' ' << p[0][1] << endl;
		cout << p[1][0] << ' ' << p[1][1] << endl;
		cout << "----------" << endl;
	}
}
