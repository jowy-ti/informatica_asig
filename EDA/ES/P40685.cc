#include <iostream>
#include <vector>
using namespace std;

typedef vector<vector<string>> Mat;

void escribir(const vector<pair<int,bool>>& res, const vector<int>& nums) {
    int size = res.size();
    bool first = false;
    cout << "{";
    for (int i = 0; i < size; ++i) {
        if (res[i].second) {
            if (first) cout << ",";
            first = true;
            cout << res[i].first;
        }
    }
    cout << "}" << endl;
}

void sub(int num, int val, int ind, vector<int>& nums, vector<pair<int,bool>>& res) {
    int n = nums.size();
    if ((val == num and num != 0) or (num == 0 and ind == n and val == num)) escribir(res, nums);
    else if (ind < n) {
        res[ind].first = nums[ind];
        res[ind].second = true;
        val += nums[ind];
        sub(num, val, ind+1, nums, res);
        res[ind].second = false;
        res[ind].first = 0;
        val -= nums[ind];
        sub(num, val, ind+1, nums, res);
    }
}
 
int main () {
    int num, op;
    cin >> num >> op;
    vector<int> nums(op);
    vector<pair<int,bool>> res(op,make_pair(0, false));
    for (int i = 0; i < op; ++i) cin >> nums[i];
    sub(num, 0, 0, nums, res);
}
