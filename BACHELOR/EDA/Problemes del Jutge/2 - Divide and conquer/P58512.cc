// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <map>
#include <string>
#include <iomanip>
using namespace std;

double exp_rapida(double x, int n) {
	if (n == 0) return 1;
	else {
		double y = exp_rapida(x, n / 2);
		if (n % 2 == 0) return y * y;
		else return y * y * x;
	}
}

int buscar_dia(int min, int max, double bank_daily, double q, double f) {
	if (min <= max) {
		int m = (max+min) / 2;
		double retornar_bank = exp_rapida(bank_daily, m) * q;
		double retornar_pavo = f * m+q;
		if (retornar_pavo > retornar_bank) return buscar_dia(m+1, max, bank_daily, q, f);
		else if (retornar_pavo < retornar_bank) return buscar_dia(min, m-1, bank_daily, q, f);
		else return m;
	} else return min;
}


int main() {
	double m, f, r;
	while (cin >> m >> f >> r) {
		double bank_daily_int = (r / 100)+1;
		cout << buscar_dia(1, 100000000, bank_daily_int, m, f) << endl;
	}
}
