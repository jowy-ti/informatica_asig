#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<char>> Mat;
typedef vector<vector<bool>> Bol;

void esc(const Mat& res) {
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            cout << res[i][j];
            if (j+1 != 9) cout << " ";
        }
        cout << endl;
    }
}
 
void emp(bool& fet, int indi, int indj, Mat& res, Bol& vis_fil, Bol& vis_col, Bol& vis_quad) {
    if (indi+indj == 17 and !fet) {
        fet = true;
        esc(res);
    }
    else if (!fet) {
        if (res[indi][indj] != '.') {
            if (indj < 8 or (indi == 8 and indj == 8)) emp(fet, indi, indj+1, res, vis_fil, vis_col, vis_quad);
            else emp(fet, indi+1, 0, res, vis_fil, vis_col, vis_quad);
        }
        else {
            for (int val = 0; val < 9; ++val) {
                int i1 = indi/3;
                int j1 = indj/3;
                if (res[indi][indj] == '.' and !vis_fil[indi][val] and !vis_col[indj][val] and !vis_quad[i1*3+j1][val]) {
                    vis_fil[indi][val] = true;
                    vis_col[indj][val] = true;
                    vis_quad[i1*3+j1][val] = true;
                    res[indi][indj] = '1'+val;
                    if (indj < 8 or (indi == 8 and indj == 8)) emp(fet, indi, indj+1, res, vis_fil, vis_col, vis_quad);
                    else emp(fet, indi+1, 0, res, vis_fil, vis_col, vis_quad);
                    vis_fil[indi][val] = false;
                    vis_col[indj][val] = false;
                    vis_quad[i1*3+j1][val] = false;
                    res[indi][indj] = '.';
                }
            }
        }
    }
}
 
int main () {
    int num, val, i1, j1;
    bool fet;
    cin >> num;
    cout << num << endl;
    for (int z = 0; z < num; ++z) {
        fet = false;
        Mat res(9,vector<char>(9));
        Bol vis_fil(9,vector<bool>(9,false));
        Bol vis_col(9,vector<bool>(9,false));
        Bol vis_quad(9,vector<bool>(9,false));
        for (int i = 0; i < 9; ++i) {
            for (int j = 0; j < 9; ++j) {
                cin >> res[i][j];
                if (res[i][j] != '.') {
                    val = res[i][j]-'0';
                    i1 = i/3;
                    j1 = j/3;
                    vis_fil[i][val-1] = true;
                    vis_col[j][val-1] = true;
                    vis_quad[i1*3+j1][val-1] = true;
                }
            }
        }
        cout << endl;
        emp(fet, 0, 0, res, vis_fil, vis_col, vis_quad);
    }
}
