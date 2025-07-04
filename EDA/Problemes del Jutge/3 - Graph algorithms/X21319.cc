// (c) FIBerHub, https://fiberhub.tk

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

#define OUTPUT 0
#define INPUT 1
#define OTRO 2
#define AND 30
#define OR 40
#define NOT 50

struct info_nodo {
	int io;
	int operacion;
	int refs;
	int valor;
	int op1;
	int op2;
};

unordered_map <string, int> nombre_int;
vector <info_nodo> nodos;

vector <int> entradas;
vector <int> salidas;
int inputs, outputs;
vector <int> valores;

bool topological_sort(int nodo) {
	if (valores[nodo] != -1) {
		return valores[nodo];
	} else   {
		if (nodos[nodo].operacion == AND) {
			valores[nodo] = topological_sort(nodos[nodo].op1) && topological_sort(nodos[nodo].op2);
			return valores[nodo];
		} else if (nodos[nodo].operacion == OR)   {
			valores[nodo] = topological_sort(nodos[nodo].op1) || topological_sort(nodos[nodo].op2);
			return valores[nodo];
		} else if (nodos[nodo].operacion == NOT)   {
			valores[nodo] = (!topological_sort(nodos[nodo].op1));
			return valores[nodo];
		}
	}
}

int main() {
	string s;
	cin >> s;
	cin >> s;
	int i = 0;

	while (s != "END") {
		info_nodo aux;
		aux.io = OUTPUT;
		aux.refs = 0;

		nodos.push_back(aux);
		nombre_int[s] = i;
		salidas.push_back(i);
		++i;
		cin >> s;
		++outputs;
	}
	cin >> s;
	cin >> s;

	while (s != "END") {
		info_nodo aux;
		aux.io = INPUT;
		aux.refs = 0;

		nodos.push_back(aux);
		nombre_int[s] = i;
		entradas.push_back(i);
		++i;
		cin >> s;
		++inputs;
	}
	string op, res, op1, op2;
	cin >> op;
	while (op != "END") {
		if (op == "AND") {
			cin >> res;
			cin >> op1 >> op2;
			if (nombre_int.find(res) == nombre_int.end()) {
				info_nodo aux;
				aux.io = OTRO;
				aux.refs = 0;

				nodos.push_back(aux);
				nombre_int.insert(make_pair(res, i));
				++i;
			}
			if (nombre_int.find(op1) == nombre_int.end()) {
				info_nodo aux;
				aux.io = OTRO;

				aux.refs = 0;
				nodos.push_back(aux);
				nombre_int.insert(make_pair(op1, i));
				++i;
			}
			if (nombre_int.find(op2) == nombre_int.end()) {
				info_nodo aux;
				aux.io = OTRO;

				aux.refs = 0;
				nodos.push_back(aux);
				nombre_int.insert(make_pair(op2, i));
				++i;
			}

			int nodo_res = nombre_int[res];
			nodos[nodo_res].operacion = AND;
			nodos[nodo_res].op1 = (nombre_int[op1]);
			nodos[nodo_res].op2 = (nombre_int[op2]);
			++nodos[nombre_int[op1]].refs;
			++nodos[nombre_int[op2]].refs;
		} else if (op == "OR")   {
			cin >> res;
			cin >> op1 >> op2;
			if (nombre_int.find(res) == nombre_int.end()) {
				info_nodo aux;

				aux.io = OTRO;
				aux.refs = 0;
				nodos.push_back(aux);
				nombre_int.insert(make_pair(res, i));
				++i;
			}
			if (nombre_int.find(op1) == nombre_int.end()) {
				info_nodo aux;

				aux.io = OTRO;
				aux.refs = 0;
				nodos.push_back(aux);
				nombre_int.insert(make_pair(op1, i));
				++i;
			}
			if (nombre_int.find(op2) == nombre_int.end()) {
				info_nodo aux;

				aux.io = OTRO;
				aux.refs = 0;
				nodos.push_back(aux);
				nombre_int.insert(make_pair(op2, i));
				++i;
			}
			int nodo_res = nombre_int[res];
			nodos[nodo_res].operacion = OR;
			nodos[nodo_res].op1 = (nombre_int[op1]);
			nodos[nodo_res].op2 = (nombre_int[op2]);
			++nodos[nombre_int[op1]].refs;
			++nodos[nombre_int[op2]].refs;
		} else if (op == "NOT")   {
			cin >> res;
			cin >> op1;
			if (nombre_int.find(res) == nombre_int.end()) {
				info_nodo aux;

				aux.io = OTRO;
				aux.refs = 0;
				nodos.push_back(aux);
				nombre_int.insert(make_pair(res, i));
				++i;
			}
			if (nombre_int.find(op1) == nombre_int.end()) {
				info_nodo aux;

				aux.io = OTRO;
				aux.refs = 0;
				nodos.push_back(aux);
				nombre_int.insert(make_pair(op1, i));
				++i;
			}
			int nodo_res = nombre_int[res];
			nodos[nodo_res].operacion = NOT;
			nodos[nodo_res].op1 = (nombre_int[op1]);
			++nodos[nombre_int[op1]].refs;
		}
		cin >> op;
	}
	char value;
	while (cin >> value) {
		valores = vector <int> (nodos.size(), -1);
		for (int j = 0; j < inputs; ++j) {
			if (value == 'T') valores[entradas[j]] = 1;
			else valores[entradas[j]] = 0;
			if (j+1 != inputs) cin >> value;
		}
		for (int j = 0; j < outputs; ++j) {
			if (nodos[salidas[j]].refs == 0) topological_sort(salidas[j]);
		}
		for (int j = 0; j < outputs; ++j) {
			if (valores[salidas[j]]) cout << "T";
			else cout << "F";
			if (j+1 != outputs) cout << " ";
		}
		cout << endl;
	}
}
