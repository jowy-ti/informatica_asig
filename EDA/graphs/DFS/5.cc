#include <iostream>
#include <vector>
#include <string>
using namespace std;

typedef vector<vector<string>> Mat;
typedef vector<vector<bool>> Matbool;

void dfs(Matbool& visit, const Mat& graf, double& sum, double& cont, int i, int j) {
    int size_fil = graf.size();
    int size_col = graf[0].size();
    int i_next = i+1;
    int i_ant = i-1;
    int j_next = j+1;
    int j_ant = j-1;
    
    if (i_next < size_fil and j_next < size_col and !visit[i_next][j_next] and graf[i_next][j_next] != "X") {
        ++cont;
        sum += stoi (graf[i_next][j_next], nullptr, 10);
        visit[i_next][j_next] = true;
        dfs(visit, graf, sum, cont, i_next, j_next);
    }
    if (i_ant >= 0 and j_ant >= 0 and !visit[i_ant][j_ant] and graf[i_ant][j_ant] != "X") {
        ++cont;
        sum += stoi (graf[i_ant][j_ant], nullptr, 10);
        visit[i_ant][j_ant] = true;
        dfs(visit, graf, sum, cont, i_ant, j_ant);
    }
    if (i_next < size_fil and j_ant >= 0 and !visit[i_next][j_ant] and graf[i_next][j_ant] != "X") {
        ++cont;
        sum += stoi (graf[i_next][j_ant], nullptr, 10);
        visit[i_next][j_ant] = true;
        dfs(visit, graf, sum, cont, i_next, j_ant);
    }
    if (i_ant >= 0 and j_next < size_col and !visit[i_ant][j_next] and graf[i_ant][j_next] != "X") {
        ++cont;
        sum += stoi (graf[i_ant][j_next], nullptr, 10);
        visit[i_ant][j_next] = true;
        dfs(visit, graf, sum, cont, i_ant, j_next);
    }
}

void bishops(Matbool& visit, const Mat& graf, int z) {
    double sum = 0;
    double cont = 1;
    double comp1 = 0;
    double comp2 = -1;
    int size_fil = graf.size();
    int size_col = graf[0].size();
    for (int i = 0; i < size_fil; ++i) {
        for (int j = 0; j < size_col; ++j) {
            if (!visit[i][j] and graf[i][j] != "X") {
                sum = stoi(graf[i][j], nullptr, 10);
                cont = 1;
                visit[i][j] = true;
                dfs(visit, graf, sum, cont, i, j);
                comp1 = sum/cont;
                int xd = comp1;
                if (comp2 == -1) {
                    if (comp1-xd != 0) {
                        cout << "Case " << z << ": no" << endl;
                        return;
                    }
                }
                else if (comp1 != comp2 or comp1-xd != 0) {
                    cout << "Case " << z << ": no" << endl;
                    return;
                }
                comp2 = comp1;
            }
        }
    }
    cout << "Case " << z << ": yes" << endl;
}

int main() {
    int num, fil, col;
    cin >> num;
    for (int z = 0; z < num; ++z) {
        cin >> fil >> col;
        Mat graf(fil, vector<string>(col));
        Matbool visit(fil, vector<bool>(col, false));
        for (int i = 0; i < fil; ++i) {
            for (int j = 0; j < col; ++j) {
                cin >> graf[i][j];
            }
        }
        bishops(visit, graf, z+1);
    }
}
