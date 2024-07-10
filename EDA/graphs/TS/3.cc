#include <iostream>
#include <vector>
#include <map>
#include <queue>
using namespace std;

struct info {
    string nom1;
    string nom2;
    string op;
};

typedef map<string,info> Map_sal;
typedef map<string,vector<string>> Map_ent;
typedef map<string,pair<int,bool>> Ref;

void topsort(const Map_sal& mapa_sal, const Map_ent& mapa_ent, Ref& refer, priority_queue& Sup) {
    
    while (!Sup.empty()) {
        
    }
}

int main() {
    info val;
    Map_sal mapa_sal;
    Map_ent mapa_ent;
    Ref refer;
    priority_queue <string, vector<string>, greater<string>> Sup;
    queue<string> out;
    vector<string> abc;
    string output, input, oper, ent1, ent2, sal, bol;
    int cont_inp = 0;
    int cont = 0;
    
    cin >> output;
    while (output != "END") {
        cin >> output;
        out.push(output);
    }
    
    cin >> input;
    while (input != "END") {
        cin >> input;
        Sup.push(input);
        mapa_ent.insert(make_pair(input,abc));
        ++cont_inp;
    }
    
    cin >> oper;
    while (oper != "END") {
        cin >> sal;
        if (oper == "NOT") {
            cin >> ent1;
            refer.insert(make_pair(sal,make_pair(1,false)));
        }
        else {
            cin >> ent1 >> ent2;
            val.nom2 = ent2;
            refer.insert(make_pair(sal,make_pair(2,false)));
            mapa_ent.find(ent2)->second.push_back(sal);
        }
        cin >> oper;
        val.op = oper;
        val.nom1 = ent1;
        mapa_sal.insert(make_pair(sal,val));
        mapa_ent.insert(make_pair(sal,abc));
        mapa_ent.find(ent1)->second.push_back(sal);
    }
    
    while (cin >> bol) {
        ++cont;
        if (cont == cont_inp) {
            topsort(mapa_sal, mapa_ent, refer, Sup);
            //out queue;
            cont = 0;
        }
    }
}
