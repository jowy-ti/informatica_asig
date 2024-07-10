#include<iostream>
#include<map>
using namespace std;

void save(map<string, int>& jug, string& name) {
    map<string, int>::const_iterator it = jug.find(name);
    if (it != jug.end()) cout << name << " is already in the casino" << endl;
    else jug.insert(make_pair(name, 0));
}

void gan(map<string, int>& jug, string& name) {
    int num;
    cin >> num;
    map<string, int>::const_iterator it = jug.find(name);
    if (it == jug.end()) cout << name << " is not in the casino" << endl;
    else {
        num += it->second;
        jug[name] = num;
    }
}

void sal(map<string, int>& jug, string& name) {
    map<string, int>::const_iterator it = jug.find(name);
    if (it == jug.end()) cout << name << " is not in the casino" << endl;
    else {
        cout << name << " has won " << it->second << endl;
        jug.erase(it);
    }
}

int main() {
    map<string, int> jug; 
    string name, op;
    while (cin >> name) {
        cin >> op;
        if (op == "enters") {
            save(jug, name);
        }
        else if (op == "wins") {
            gan(jug, name);
        }
        else if (op == "leaves") {
            sal(jug, name);
        }
    }
    cout << "----------" << endl;
    for (map<string, int>::const_iterator it = jug.begin(); it != jug.end(); ++it) {
        cout << it->first << " is winning " << it->second << endl;
    }
}
