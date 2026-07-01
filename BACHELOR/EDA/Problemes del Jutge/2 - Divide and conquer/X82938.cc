// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
using namespace std;

int find_unimodal(const vector <int>& v, int i, int j) {
	if (j-i == 0) return j;
	if (j-i == 1) {
		if (v[j] > v[i]) return j;
		return i;
	}
	int mid = (i+j) / 2;
	if (v[mid-1] < v[mid] and v[mid] < v[mid+1]) return find_unimodal(v, mid+1, j);
	if (v[mid-1] > v[mid] and v[mid] > v[mid+1]) return find_unimodal(v, i, mid-1);
	return mid;
}

bool d_search(const vector <int>& v, int x, int i, int j, int mode) {
	if (j >= i) {
		int mid = (j+i) / 2;
		if (v[mid] == x) return true;
		if ((mode == 0 and v[mid] < x) or (mode == 1 and x < v[mid])) return d_search(v, x, mid+1, j, mode);
		return d_search(v, x, i, mid-1, mode);
	}
	return false;
}

bool search(int x, const vector <int>& v) {
	int pos = find_unimodal(v, 0, v.size()-1);
	if (d_search(v, x, 0, pos, 0)) return true;
	if (d_search(v, x, pos, v.size()-1, 1)) return true;
	return false;
}
