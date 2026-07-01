// (c) FIBerHub, https://fiberhub.tk

#include <vector>
#include <iostream>
using namespace std;


int first_occurrence_rec(double x, const vector <double>& v, int s, int e) {
	int pos = (s+e) / 2;
	if (s > e) return -1;
	if (x < v[pos]) return first_occurrence_rec(x, v, s, pos-1);
	else if (x > v[pos]) return first_occurrence_rec(x, v, pos+1, e);
	else {
		if (pos-1 >= 0) {
			int pos1 = first_occurrence_rec(x, v, s, pos-1);
			if (pos1 != -1) return pos1;
		}
		return pos;
	}
}


int first_occurrence(double x, const vector <double>& v) {
	if (v.empty() or x < v[0] or v[v.size()-1] < x) return -1;
	else return first_occurrence_rec(x, v, 0, v.size()-1);
}
